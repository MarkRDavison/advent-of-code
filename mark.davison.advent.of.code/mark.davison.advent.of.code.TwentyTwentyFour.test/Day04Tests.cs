namespace mark.davison.advent.of.code.TwentyTwentyFour.test;

[TestClass]
public sealed class Day04Tests
{
    [TestMethod]
    public async Task Day04Works()
    {
        var solver = new Day04();

        var (part1, part2) = await solver.Solve([
"MMMSXXMASM",
"MSAMXMSMSA",
"AMXSXMAAMM",
"MSAMASMSMX",
"XMASAMXAMM",
"XXAMMXXAMA",
"SMSMSASXSS",
"SAXAMASAAA",
"MAMMMXMMMM",
"MXMXAXMASX",
            ]);

        Assert.AreEqual("18", part1);
        Assert.AreEqual("9", part2);
    }
}
