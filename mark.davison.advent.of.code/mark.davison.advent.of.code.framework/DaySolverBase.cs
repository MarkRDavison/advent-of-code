namespace mark.davison.advent.of.code.framework;

public abstract class DaySolverBase : IDaySolver
{
    public string Name { get; private set; } = "Unset";

    public void Init(string name)
    {
        Name = name;
    }

    public abstract Task<(string Part1, string Part2)> Solve(IList<string> input);
}
