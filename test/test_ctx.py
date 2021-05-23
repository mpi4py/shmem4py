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
            if ctx:
                with ctx.create() as newctx:
                    self.assertNotEqual(newctx, ctx)
                    self.assertNotEqual(newctx, shmem.CTX_INVALID)
                self.assertEqual(newctx, shmem.CTX_INVALID)

    def testCreate(self):
        ctx = shmem.CTX_DEFAULT.create()
        self.assertNotEqual(ctx, shmem.CTX_DEFAULT)
        ctx.destroy()
        self.assertEqual(ctx, shmem.CTX_INVALID)
        for opt in options:
            ctx = shmem.CTX_DEFAULT.create(opt)
            ctx.destroy()
            ctx = shmem.CTX_DEFAULT.create(opt, shmem.TEAM_WORLD)
            ctx.destroy()
            ctx = shmem.CTX_DEFAULT.create(options=opt, team=shmem.TEAM_WORLD)
            ctx.destroy()

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

    def testQuiet(self):
        ctx = shmem.CTX_DEFAULT
        ctx.quiet()



if __name__ == '__main__':
    unittest.main()
