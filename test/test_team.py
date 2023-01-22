from shmem4py import shmem
import unittest

teams = [
    shmem.TEAM_WORLD,
    shmem.TEAM_INVALID,
]
if shmem.TEAM_SHARED:
    teams.insert(1, shmem.TEAM_SHARED)

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
        for team in teams + [shmem.TEAM_SHARED]:
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

    def testSplit(self):
        team = shmem.TEAM_WORLD
        try:
            tnew = team.split_strided()
            tnew.destroy()
        except RuntimeError:
            self.skipTest('team')
        #
        tnew = team.split_strided()
        self.assertTrue(tnew.n_pes(), team.n_pes())
        conf = tnew.get_config()
        self.assertEqual(conf['num_contexts'], 0)
        tnew.destroy()
        #
        tnew = team.split_strided(
            size=team.n_pes(),
            config=dict(num_contexts=1),
        )
        self.assertTrue(tnew.n_pes(), team.n_pes())
        conf = tnew.get_config()
        if tnew != team:
            if shmem.lib.SHMEM_TEAM_NUM_CONTEXTS:
                self.assertEqual(conf['num_contexts'], 1)
        tnew.destroy()
        #
        tnew = team.split_strided(num_contexts=2)
        conf = tnew.get_config()
        if tnew != team:
            if shmem.lib.SHMEM_TEAM_NUM_CONTEXTS:
                self.assertEqual(conf['num_contexts'], 2)
        tnew.destroy()

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

    def testCreateCtx(self):
        team = shmem.TEAM_WORLD
        try:
            ctx = team.create_ctx()
        except RuntimeError:
            pass
        else:
            ctx.destroy()
        for opt in options_ctx:
            try:
                ctx= team.create_ctx(opt)
            except RuntimeError:
                pass
            else:
                ctx.destroy()

    def testSync(self):
        team = shmem.TEAM_WORLD
        team.sync()

    def testInvalid(self):
        team = shmem.TEAM_INVALID
        self.assertRaises(RuntimeError, team.my_pe)
        self.assertRaises(RuntimeError, team.n_pes)


if __name__ == '__main__':
    unittest.main()
