
// 1st Node ..
if (IsBracket == 1)
{
    //printf("%c\n", CurrentChar);
    CollectIntigers(CurrentChar);
    IsBracket = 0;
}
if (CurrentChar == '{')
{
    IsBracket = 1;
}
if (IsComma && CurrentChar != '}')
{
    printf("%c\n", CurrentChar);
    IsComma = 0;
}
if (CurrentChar == '\n')
    IsComma = 1;

// 2nd Node ..
if (IsBetterThan && CurrentChar != ' ')
{
    printf("%c\n", CurrentChar);
    IsBetterThan = 0;
}
if (CurrentChar == '>')
    IsBetterThan = 1;

// Labels ..
if (Is1stQuote && !Is2ndQuote && CurrentChar != '"')
    printf("%c\n", CurrentChar);
if (CurrentChar == '"') // checking for the end of the String ..
{
    Count++;
    if (Count % 2 == 1)
        Is1stQuote = 1;
    else
        Is2ndQuote = 1;
}
if (Is2ndQuote) // End the String ..
    Is1stQuote = Is2ndQuote = 0;