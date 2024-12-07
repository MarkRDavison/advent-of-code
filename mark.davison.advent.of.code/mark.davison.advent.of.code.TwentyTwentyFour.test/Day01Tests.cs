namespace mark.davison.advent.of.code.TwentyTwentyFour.test;

[TestClass]
public class Day01Tests
{
    [TestMethod]
    public async Task Day01_Works()
    {
        var solver = new Day01();

        var (part1, part2) = await solver.Solve([
"3   4",
"4   3",
"2   5",
"1   3",
"3   9",
"3   3",
            ]);

        Assert.AreEqual("11", part1);
        Assert.AreEqual("31", part2);
    }
}
