from shmem4py import shmem
import unittest

teams = [
    shmem.TEAM_WORLD,
    shmem.TEAM_SHARED,
    shmem.TEAM_INVALID,
]

options_ctx = (
    shmem.CTX_PRIVATE,
    shmem.CTX_SERIALIZED,
    shmem.CTX_NOSTORE,
)

class TestTeam(unittest.TestCase):

    def testNew(self):
        team = shmem.Team()
        self.assertEqual(team, shmem.TEAM_INVALID)
        team = shmem.Team(None)
        self.assertEqual(team, shmem.TEAM_INVALID)
        val = shmem.ffi.cast('int', 0)
        self.assertRaises(TypeError, shmem.Team, val)
        self.assertRaises(TypeError, shmem.Team, 123)

    def testCmp(self):
        self.assertFalse(shmem.TEAM_INVALID == 0)
        self.assertFalse(shmem.TEAM_WORLD == 1)
        self.assertNotEqual(shmem.TEAM_INVALID, 0)
        self.assertNotEqual(shmem.TEAM_WORLD, 1)
        for i, ti in enumerate(teams):
            for j, tj in enumerate(teams):
                tk = shmem.Team(tj)
                if i == j:
                    self.assertEqual(ti, tj)
                    self.assertEqual(ti, tk)
                    self.assertTrue(ti is tj)
                    self.assertTrue(ti is not tk)
                else:
                    self.assertNotEqual(ti, tj)
                    self.assertNotEqual(ti, tk)

    def testBool(self):
        self.assertTrue(shmem.TEAM_WORLD)
        self.assertTrue(shmem.TEAM_SHARED)
        self.assertFalse(shmem.TEAM_INVALID)

    def testWith(self):
        for team in teams:
            with team as alias:
                self.assertTrue(team is alias)
            #if team:
            #    with team.create() as newteam:
            #        self.assertNotEqual(newteam, team)
            #        self.assertNotEqual(newteam, shmem.TEAM_INVALID)
            #    self.assertEqual(newteam, shmem.TEAM_INVALID)

    def testDestroy(self):
        for team in teams:
            if team:
                team.destroy()
                self.assertTrue(team)
            else:
                team.destroy()
                self.assertFalse(team)

    def testDestroyAlias(self):
        for team in teams:
            alias = shmem.Team(team)
            if team:
                self.assertTrue(alias)
            alias.destroy()
            self.assertFalse(alias)

    def testQuery(self):
        team = shmem.TEAM_WORLD
        self.assertEqual(team.my_pe(), shmem.my_pe())
        self.assertEqual(team.n_pes(), shmem.n_pes())

    def testTranslate(self):
        team = shmem.TEAM_WORLD
        tpe = team.translate_pe(team=team)
        self.assertEqual(tpe, team.my_pe())
        for pe in range(team.n_pes()):
            tpe = team.translate_pe(pe)
            self.assertEqual(tpe, pe)
            tpe = team.translate_pe(pe, team=team)
            self.assertEqual(tpe, pe)

    @unittest.skipIf('OSHMPI' in shmem.VENDOR_STRING, 'OSHMPI')
    def testCreateCtx(self):
        team = shmem.TEAM_WORLD
        ctx = team.create_ctx()
        ctx.destroy()
        for opt in options_ctx:
            ctx= team.create_ctx(opt)
            ctx.destroy()

    @unittest.skipIf('OSHMPI' in shmem.VENDOR_STRING, 'OSHMPI')
    def testSync(self):
        team = shmem.TEAM_WORLD
        team.sync()


if __name__ == '__main__':
    unittest.main()
