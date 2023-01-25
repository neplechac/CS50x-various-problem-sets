// https://cs50.harvard.edu/x/2020/psets/2/readability/

#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

void count_s(string s, int result[]);
int read_grade(int result[]);

int main(void)
{
    string s = get_string("Text: ");

    int result[3];
    count_s(s, result);

    int grade = read_grade(result);

    if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (grade >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", grade);
    }

}

void count_s(string s, int result[])
{
    result[0] = 0;
    result[1] = 1;
    result[2] = 0;

    for (int i = 0, n = strlen(s); i < n; i++)
    {
        if isalpha(s[i])
        {
            result[0]++;
        }
        else if isspace(s[i])
        {
            result[1]++;
        }
        else if (s[i] == '.' || s[i] == '?' || s[i] == '!')
        {
            result[2]++;
        }
    }
}

int read_grade(int result[])
{
    float L = (100.0 / result[1]) * result[0];
    float S = (100.0 / result[1]) * result[2];

    float index = 0.0588 * L - 0.296 * S - 15.8;

    return round(index);
}



