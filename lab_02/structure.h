#ifndef _STRUCT_H
#define _STRUCT_H

#pragma pack(push, 1)

struct technical
{
    char *industry_type;
    char *country;
    int published_year;
};

struct artistic
{
    char *artistic_genre;
};

struct children
{
    char *children_genre;
};

struct table_inf
{
    char *surname;
    char *book_name;
    char *publishing_house;
    int pages;
    char *literature_type;
    union
    {
        struct technical;
        struct artistic;
        struct children;
    };
};

#pragma pack(pop)

#endif