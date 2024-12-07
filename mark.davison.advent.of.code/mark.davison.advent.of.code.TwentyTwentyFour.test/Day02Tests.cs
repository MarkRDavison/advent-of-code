namespace mark.davison.advent.of.code.TwentyTwentyFour.test;

[TestClass]
public class Day02Tests
{
    [TestMethod]
    public async Task Day02Works()
    {
        var solver = new Day02();

        var (part1, part2) = await solver.Solve([
"7 6 4 2 1",
"1 2 7 8 9",
"9 7 6 2 1",
"1 3 2 4 5",
"8 6 4 4 1",
"1 3 6 7 9",
            ]);

        Assert.AreEqual("2", part1);
        Assert.AreEqual("4", part2);
    }

    [DataRow(7, 6, 4, 2, 1, true)]
    [DataRow(1, 2, 7, 8, 9, false)]
    [DataRow(9, 7, 6, 2, 1, false)]
    [DataRow(1, 3, 2, 4, 5, false)]
    [DataRow(8, 6, 4, 4, 1, false)]
    [DataRow(1, 3, 6, 7, 9, true)]
    [DataTestMethod]
    public void IsReportSafe_Works(int l0, int l1, int l2, int l3, int l4, bool isSafe)
    {
        Assert.AreEqual(isSafe, Day02.IsReportSafe([l0, l1, l2, l3, l4]));
    }
}
