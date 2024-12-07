namespace mark.davison.advent.of.code.framework;

[AttributeUsage(AttributeTargets.Class, AllowMultiple = false)]
public sealed class DayAttribute : Attribute
{
    public required int Year { get; set; }
    public required int Day { get; set; }
    public required string Name { get; set; }
}
