from shmem4py import shmem
import unittest

ctxs = [
    shmem.CTX_DEFAULT,
    shmem.CTX_INVALID,
]

options = (
    shmem.CTX_PRIVATE,
    shmem.CTX_SERIALIZED,
    shmem.CTX_NOSTORE,
)

class TestCtx(unittest.TestCase):

    def testNew(self):
        ctx = shmem.Ctx()
        self.assertEqual(ctx, shmem.CTX_INVALID)
        ctx = shmem.Ctx(None)
        self.assertEqual(ctx, shmem.CTX_INVALID)
        val = shmem.ffi.cast('int', 0)
        self.assertRaises(TypeError, shmem.Ctx, val)
        self.assertRaises(TypeError, shmem.Ctx, 123)

    def testCmp(self):
        self.assertFalse(shmem.CTX_INVALID == 0)
        self.assertFalse(shmem.CTX_DEFAULT == 1)
        self.assertNotEqual(shmem.CTX_INVALID, 0)
        self.assertNotEqual(shmem.CTX_DEFAULT, 1)
        for i, ci in enumerate(ctxs):
            for j, cj in enumerate(ctxs):
                ck = shmem.Ctx(cj)
                if i == j:
                    self.assertEqual(ci, cj)
                    self.assertEqual(ci, ck)
                    self.assertTrue(ci is cj)
                    self.assertTrue(ci is not ck)
                else:
                    self.assertNotEqual(ci, cj)
                    self.assertNotEqual(ci, ck)

    def testBool(self):
        self.assertTrue(shmem.CTX_DEFAULT)
        self.assertFalse(shmem.CTX_INVALID)

    def testWith(self):
        for ctx in ctxs:
            with ctx as alias:
                self.assertTrue(ctx is alias)

    def testWithNew(self):
        for ctx in ctxs:
            if not ctx: continue
            try:
                newctx = shmem.Ctx.create()
            except RuntimeError:
                continue
            with newctx:
                self.assertNotEqual(newctx, ctx)
                self.assertNotEqual(newctx, shmem.CTX_INVALID)
            self.assertEqual(newctx, shmem.CTX_INVALID)

    def testCreate(self):
        try:
            ctx = shmem.Ctx.create()
        except RuntimeError:
            pass
        else:
            self.assertNotEqual(ctx, shmem.CTX_DEFAULT)
            ctx.destroy()
            self.assertEqual(ctx, shmem.CTX_INVALID)
        try:
            ctx = shmem.Ctx.create(team=shmem.TEAM_WORLD)
        except RuntimeError:
            pass
        else:
            self.assertNotEqual(ctx, shmem.CTX_DEFAULT)
            ctx.destroy()
            self.assertEqual(ctx, shmem.CTX_INVALID)

    @unittest.skipIf('open-mpi' in shmem.VENDOR_STRING, 'open-mpi')
    def testCreateOptions(self):
        def create(*args, **kwargs):
            try:
                ctx = shmem.Ctx.create(*args, **kwargs)
            except RuntimeError:
                pass
            else:
                self.assertNotEqual(ctx, shmem.CTX_INVALID)
                self.assertNotEqual(ctx, shmem.CTX_DEFAULT)
                ctx.destroy()
                self.assertEqual(ctx, shmem.CTX_INVALID)

        for opt in options:
            create(opt)
            create(opt, shmem.TEAM_WORLD)
            create(options=opt, team=shmem.TEAM_WORLD)

    def testDestroy(self):
        for ctx in ctxs:
            if ctx:
                ctx.destroy()
                self.assertTrue(ctx)
            else:
                ctx.destroy()
                self.assertFalse(ctx)

    def testDestroyAlias(self):
        for ctx in ctxs:
            alias = shmem.Ctx(ctx)
            if ctx:
                self.assertTrue(alias)
            alias.destroy()
            self.assertFalse(alias)

    def testGetTeam(self):
        ctx = shmem.CTX_DEFAULT
        team = ctx.get_team()
        self.assertEqual(team, shmem.TEAM_WORLD)
        team.destroy()

    def testFence(self):
        ctx = shmem.CTX_DEFAULT
        ctx.fence()
        shmem.fence(ctx)

    def testQuiet(self):
        ctx = shmem.CTX_DEFAULT
        ctx.quiet()
        shmem.quiet(ctx)

    def testInvalid(self):
        ctx = shmem.CTX_INVALID
        self.assertRaises(RuntimeError, ctx.get_team)


if __name__ == '__main__':
    unittest.main()
