namespace mark.davison.advent.of.code.TwentyTwentyFour.test;

[TestClass]
public sealed class Day03Tests
{
    [TestMethod]
    public async Task Day03_Part1Works()
    {
        var solver = new Day03();

        var (part1, part2) = await solver.Solve([
"xmul(2,4)%&mul[3,7]!@^do_not_mul(5,5)+mul(32,64]then(mul(11,8)mul(8,5))"
            ]);

        Assert.AreEqual("161", part1);
    }
    [TestMethod]
    public async Task Day03_Part2Works()
    {
        var solver = new Day03();

        var (part1, part2) = await solver.Solve([
"xmul(2,4)&mul[3,7]!^don't()_mul(5,5)+mul(32,64](mul(11,8)undo()?mul(8,5))"
            ]);

        Assert.AreEqual("48", part2);
    }
}
