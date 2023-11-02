//Movie Library management

//****** There maybe some error in handling files code *****

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct
{
    char title[100];
    char genre[50];
    int year;
    char director[100];
    char language[50];
} Movie;

void login();
void welcomeMenu();
void addMovie(FILE *fptr);
void searchMovieByName(FILE *fptr);
void searchMovieByDirector(FILE *fptr);
void searchMovieByLanguage(FILE *fptr);
void searchMovieByReleaseDate(FILE *fptr);
void deleteMovieByName(FILE *fptr);
void deleteMoviesByGenre(FILE *fptr);
void deleteMoviesByYear(FILE *fptr);
void deleteMoviesByDirector(FILE *fptr);
void deleteMoviesByLanguage(FILE *fptr);
void displayAllMoviesSortedByYear(FILE *fptr);
void countMovies(FILE *fptr);
void deleteLibrary(FILE *fptr);
void editMovieDetails(FILE *fptr);

int main()
{
    FILE *fptr;

    login();

    fptr = fopen("movies.txt", "a+");
    if (fptr == NULL)
    {
        printf("Error opening file.\n");
        return 1;
    }

    welcomeMenu(fptr);

    fclose(fptr);

    return 0;
}

void login()
{
    char username[20];
    char password[20];
    int attempts = 0;

    while (attempts < 5)
    {
        system("cls");

        printf("\t\t\t\t\t \033[5;101;97m Welcome to Movie Library management System \033[0m");
        printf("\n\n\n\n\n\t\t\t\t\033[30;103mUsername:\033[0m ");
        fgets(username, sizeof(username), stdin);
        printf("\n\t\t\t\t\033[30;103mPassword:\033[0m ");
        fgets(password, sizeof(password), stdin);


        username[strcspn(username, "\n")] = '\0';
        password[strcspn(password, "\n")] = '\0';

        if (strcmp(username, "admin") == 0 && strcmp(password, "sifat") == 0)
        {
            printf("\033[5;97;42m"); // Set text color to white and background color to light green
            printf("\n\n\nLogin Successful.\n");
            printf("Press Enter to Continue");
            printf("\033[0m"); // Reset colors to default
            getchar();
            break;
        }
        else
        {
            attempts++;
            printf("\n\n\n\033[5;101;97mInvalid username or password. Please try again.\033[0m\n");
            printf("Attempts Remaining %d",5-attempts);
            if (attempts == 5)
            {
                printf("\n\033[5;101;97mMaximum login attempts reached. Exiting...\033[0m\n");
                exit(0);
            }
            printf("\nPress Enter to try again\n");

            getchar();
        }
    }


}

void welcomeMenu(FILE *fptr)
{
    int choice;

    while (1)
    {
        system("cls");
        printf("\t\t\t\t\t\033[96;40m===== Movie Library Management =====\033[0m\n");
        printf("\n\n\n");
        printf("\033[97;42m");
        printf("\t\t\t\t\t1. Add a Movie\n");
        printf("\t\t\t\t\t2. Search for a Movie\n");
        printf("\t\t\t\t\t3. Delete a Movie\n");
        printf("\t\t\t\t\t4. Delete Multiple Movies\n");
        printf("\t\t\t\t\t5. Display All Movies Sorted by Year\n");
        printf("\t\t\t\t\t6. Edit Movie Details\n");
        printf("\t\t\t\t\t7. Count Movies in Library\n");
        printf("\t\t\t\t\t8. Delete the Whole Library\n");
        printf("\t\t\t\t\t9. Exit\n");
        printf("\033[0m");
        printf("\n\n\n");
        printf("\t\t\t\t\t\033[5;36;40m===============================\033[0m\n");
        printf("\n\nEnter your choice: ");
        scanf("%d", &choice);
        fflush(stdin);

        switch (choice)
        {
        case 1:
            system("Color A");
            addMovie(fptr);
            break;
        case 2:
            system("Color A");
            printf("\t\t\t1. Search by Name\n");
            printf("\t\t\t2. Search by Director\n");
            printf("\t\t\t3. Search by Language\n");
            printf("\t\t\t4. Search by Release Date\n");
            printf("Enter your choice: ");
            scanf("%d", &choice);
            fflush(stdin);

            switch (choice)
            {
            case 1:
                system("Color A");
                searchMovieByName(fptr);
                break;
            case 2:
                system("Color A");
                searchMovieByDirector(fptr);
                break;
            case 3:
                system("Color A");
                searchMovieByLanguage(fptr);
                break;
            case 4:
                system("Color A");
                searchMovieByReleaseDate(fptr);
                break;
            default:
                system("Color A");
                printf("Invalid choice. Please try again.\n");
            }
            break;
        case 3:
            system("Color A");
            deleteMovieByName(fptr);
            break;
        case 4:
            system("Color A");
            printf("\t\t\t1. Delete by Genre\n");
            printf("\t\t\t2. Delete by Year\n");
            printf("\t\t\t3. Delete by Director\n");
            printf("\t\t\t4. Delete by Language\n");
            printf("Enter your choice: ");
            scanf("%d", &choice);
            fflush(stdin);

            switch (choice)
            {
            case 1:
                system("Color A");
                deleteMoviesByGenre(fptr);
                break;
            case 2:
                system("Color A");
                deleteMoviesByYear(fptr);
                break;
            case 3:
                system("Color A");
                deleteMoviesByDirector(fptr);
                break;
            case 4:
                system("Color A");
                deleteMoviesByLanguage(fptr);
                break;
            default:
                system("Color C");
                printf("Invalid choice. Please try again.\n");
            }
            break;
        case 5:
            system("Color A");
            displayAllMoviesSortedByYear(fptr);
            break;
        case 6:
            system("Color A");
            editMovieDetails(fptr);
            break;
        case 7:
            system("Color A");
            countMovies(fptr);
            break;
        case 8:
            system("Color A");
            deleteLibrary(fptr);
            break;
        case 9:
            system("Color A");
            printf("\033[91mExiting...\033[0m\n");
            return;
        default:
            system("Color C");
            printf("Invalid choice. Please try again.\n");
        }

        printf("Press Enter to continue...\n");
        getchar();
    }
}

void addMovie(FILE *fptr)
{
    Movie movie;

    fflush(stdin);
    system("cls");
    printf("=== Add a Movie ===\n");
    printf("\n\n\n");
    printf("Title: ");
    fgets(movie.title, sizeof(movie.title), stdin);
    printf("Genre: ");
    fgets(movie.genre, sizeof(movie.genre), stdin);
    printf("Year: ");
    scanf("%d", &movie.year);
    fflush(stdin);
    printf("Director: ");
    fgets(movie.director, sizeof(movie.director), stdin);
    printf("Language: ");
    fgets(movie.language, sizeof(movie.language), stdin);

    fwrite(&movie, sizeof(Movie), 1, fptr);
    printf("\n\n\n");
    printf("Movie added successfully.\n");
}

void searchMovieByName(FILE *fptr)
{
    char searchTitle[100];
    Movie movie;

    fflush(stdin);
    system("cls");
    printf("=== Search by Name ===\n");
    printf("Enter the title to search: ");
    fgets(searchTitle, sizeof(searchTitle), stdin);

    rewind(fptr);

    while (fread(&movie, sizeof(Movie), 1, fptr) == 1)
    {
        if (strcmp(movie.title, searchTitle) == 0)
        {
            printf("Movie Found:\n");
            printf("Title: %s", movie.title);
            printf("Genre: %s", movie.genre);
            printf("Year: %d\n", movie.year);
            printf("Director: %s", movie.director);
            printf("Language: %s", movie.language);
            return;
        }
    }

    printf("Movie not found.\n");
}



void searchMovieByDirector(FILE *fptr)
{
    char searchDirector[100];
    Movie movie;

    fflush(stdin);
    system("cls");
    printf("=== Search by Director ===\n");
    printf("Enter the director to search: ");
    fgets(searchDirector, sizeof(searchDirector), stdin);

    rewind(fptr);

    while (fread(&movie, sizeof(Movie), 1, fptr) == 1)
    {
        if (strcmp(movie.director, searchDirector) == 0)
        {
            printf("Movie Found:\n");
            printf("Title: %s", movie.title);
            printf("Genre: %s", movie.genre);
            printf("Year: %d\n", movie.year);
            printf("Director: %s", movie.director);
            printf("Language: %s", movie.language);
            return;
        }
    }

    printf("Movie not found.\n");
}

void searchMovieByLanguage(FILE *fptr)
{
    char searchLanguage[50];
    Movie movie;

    fflush(stdin);
    system("cls");
    printf("=== Search by Language ===\n");
    printf("Enter the language to search: ");
    fgets(searchLanguage, sizeof(searchLanguage), stdin);

    rewind(fptr);

    while (fread(&movie, sizeof(Movie), 1, fptr) == 1)
    {
        if (strcmp(movie.language, searchLanguage) == 0)
        {
            printf("Movie Found:\n");
            printf("Title: %s", movie.title);
            printf("Genre: %s", movie.genre);
            printf("Year: %d\n", movie.year);
            printf("Director: %s", movie.director);
            printf("Language: %s", movie.language);
            return;
        }
    }

    printf("Movie not found.\n");
}

void searchMovieByReleaseDate(FILE *fptr)
{
    int searchYear;
    Movie movie;

    fflush(stdin);
    system("cls");
    printf("=== Search by Release Date ===\n");
    printf("Enter the year to search: ");
    scanf("%d", &searchYear);
    fflush(stdin);

    while (fread(&movie, sizeof(Movie), 1, fptr) == 1)
    {
        if (movie.year == searchYear)
        {
            printf("Movie Found:\n");
            printf("Title: %s", movie.title);
            printf("Genre: %s", movie.genre);
            printf("Year: %d\n", movie.year);
            printf("Director: %s", movie.director);
            printf("Language: %s", movie.language);
            return;
        }
    }

    printf("Movie not found.\n");
}

void deleteMovieByName(FILE *fptr)
{
    char searchTitle[100];
    FILE *tempFile;
    Movie movie;
    int found = 0;

    fflush(stdin);
    system("cls");
    printf("=== Delete Movie ===\n");
    printf("Enter the title to delete: ");
    fgets(searchTitle, sizeof(searchTitle), stdin);

    tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL)
    {
        printf("Error opening temporary file.\n");
        return;
    }

    rewind(fptr);

    while (fread(&movie, sizeof(Movie), 1, fptr) == 1)
    {
        if (strcmp(movie.title, searchTitle) != 0)
        {
            fwrite(&movie, sizeof(Movie), 1, tempFile);
        }
        else
        {
            found = 1;
        }
    }

    fclose(fptr);
    fclose(tempFile);

    remove("movies.txt");
    rename("temp.txt", "movies.txt");

    fptr = fopen("movies.txt", "a+");

    if (found)
    {
        printf("Movie deleted successfully.\n");
    }
    else
    {
        printf("Movie not found.\n");
    }
}

void deleteMoviesByGenre(FILE *fptr)
{
    char searchGenre[50];
    FILE *tempFile;
    Movie movie;
    int found = 0;

    fflush(stdin);
    system("cls");
    printf("=== Delete Movies by Genre ===\n");
    printf("Enter the genre to delete: ");
    fgets(searchGenre, sizeof(searchGenre), stdin);

    tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL)
    {
        printf("Error opening temporary file.\n");
        return;
    }

    rewind(fptr);

    while (fread(&movie, sizeof(Movie), 1, fptr) == 1)
    {
        if (strcmp(movie.genre, searchGenre) != 0)
        {
            fwrite(&movie, sizeof(Movie), 1, tempFile);
        }
        else
        {
            found = 1;
        }
    }

    fclose(fptr);
    fclose(tempFile);

    remove("movies.txt");
    rename("temp.txt", "movies.txt");

    fptr = fopen("movies.txt", "a+");

    if (found)
    {
        printf("Movies deleted successfully.\n");
    }
    else
    {
        printf("No movies found with the specified genre.\n");
    }
}

void deleteMoviesByYear(FILE *fptr)
{
    int searchYear;
    FILE *tempFile;
    Movie movie;
    int found = 0;

    fflush(stdin);
    system("cls");
    printf("=== Delete Movies by Year ===\n");
    printf("Enter the year to delete: ");
    scanf("%d", &searchYear);

    tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL)
    {
        printf("Error opening temporary file.\n");
        return;
    }

    rewind(fptr);

    while (fread(&movie, sizeof(Movie), 1, fptr) == 1)
    {
        if (movie.year != searchYear)
        {
            fwrite(&movie, sizeof(Movie), 1, tempFile);
        }
        else
        {
            found = 1;
        }
    }

    fclose(fptr);
    fclose(tempFile);

    remove("movies.txt");
    rename("temp.txt", "movies.txt");

    fptr = fopen("movies.txt", "a+");

    if (found)
    {
        printf("Movies deleted successfully.\n");
    }
    else
    {
        printf("No movies found with the specified year.\n");
    }
}

void deleteMoviesByDirector(FILE *fptr)
{
    char searchDirector[100];
    FILE *tempFile;
    Movie movie;
    int found = 0;

    fflush(stdin);
    system("cls");
    printf("=== Delete Movies by Director ===\n");
    printf("Enter the director to delete: ");
    fgets(searchDirector, sizeof(searchDirector), stdin);

    tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL)
    {
        printf("Error opening temporary file.\n");
        return;
    }

    rewind(fptr);

    while (fread(&movie, sizeof(Movie), 1, fptr) == 1)
    {
        if (strcmp(movie.director, searchDirector) != 0)
        {
            fwrite(&movie, sizeof(Movie), 1, tempFile);
        }
        else
        {
            found = 1;
        }
    }

    fclose(fptr);
    fclose(tempFile);

    remove("movies.txt");
    rename("temp.txt", "movies.txt");

    fptr = fopen("movies.txt", "a+");

    if (found)
    {
        printf("Movies deleted successfully.\n");
    }
    else
    {
        printf("No movies found with the specified director.\n");
    }
}


void deleteMoviesByLanguage(FILE *fptr)
{
    char searchLanguage[50];
    FILE *tempFile;
    Movie movie;
    int found = 0;

    fflush(stdin);
    system("cls");
    printf("=== Delete Movies by Language ===\n");
    printf("Enter the language to delete: ");
    fgets(searchLanguage, sizeof(searchLanguage), stdin);

    tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL)
    {
        printf("Error opening temporary file.\n");
        return;
    }

    rewind(fptr);

    while (fread(&movie, sizeof(Movie), 1, fptr) == 1)
    {
        if (strcmp(movie.language, searchLanguage) != 0)
        {
            fwrite(&movie, sizeof(Movie), 1, tempFile);
        }
        else
        {
            found = 1;
        }
    }

    fclose(fptr);
    fclose(tempFile);

    remove("movies.txt");
    rename("temp.txt", "movies.txt");

    fptr = fopen("movies.txt", "a+");

    if (found)
    {
        printf("Movies deleted successfully.\n");
    }
    else
    {
        printf("No movies found with the specified language.\n");
    }
}

void displayAllMoviesSortedByYear(FILE *fptr)
{
    int count = 0;
    Movie *movies;
    Movie temp;

    fflush(stdin);
    system("cls");
    printf("=== All Movies Sorted by Year ===\n");

    rewind(fptr);

    while (fread(&temp, sizeof(Movie), 1, fptr) == 1)
    {
        count++;
    }

    if (count == 0)
    {
        printf("No movies found.\n");
        return;
    }

    movies = (Movie *)malloc(count * sizeof(Movie));

    rewind(fptr);

    count = 0;
    while (fread(&movies[count], sizeof(Movie), 1, fptr) == 1)
    {
        count++;
    }

    for (int i = 0; i < count - 1; i++)
    {
        for (int j = 0; j < count - i - 1; j++)
        {
            if (movies[j].year < movies[j + 1].year)
            {
                temp = movies[j];
                movies[j] = movies[j + 1];
                movies[j + 1] = temp;
            }
        }
    }

    for (int i = 0; i < count; i++)
    {
        printf("Title: %s", movies[i].title);
        printf("Genre: %s", movies[i].genre);
        printf("Year: %d\n", movies[i].year);
        printf("Director: %s", movies[i].director);
        printf("Language: %s", movies[i].language);
        printf("===============================\n");
    }

    free(movies);
    return;
}

void countMovies(FILE *fptr)
{
    int count = 0;
    Movie movie;

    fflush(stdin);
    system("cls");
    printf("=== Count Movies ===\n");

    rewind(fptr);

    while (fread(&movie, sizeof(Movie), 1, fptr) == 1)
    {
        count++;
    }

    printf("Total number of movies: %d\n", count);
}

void deleteLibrary(FILE *fptr)
{
    fflush(stdin);
    system("cls");
    printf("\t\t=== Delete Library ===\n");

    if (remove("movies.txt") == 0)
    {
        printf("Library deleted successfully.\n");
    }
    else
    {
        printf("Error deleting library.\n");
    }

    fptr = fopen("movies.txt", "a+");
}

void editMovieDetails(FILE *fptr)
{
    int count = 0;
    Movie *movies;
    Movie temp;

    fflush(stdin);
    system("cls");
    printf("=== Edit Movie Details ===\n");

    rewind(fptr);

    while (fread(&temp, sizeof(Movie), 1, fptr) == 1)
    {
        count++;
    }

    if (count == 0)
    {
        printf("No movies found.\n");
        return;
    }

    movies = (Movie *)malloc(count * sizeof(Movie));

    rewind(fptr);

    count = 0;
    while (fread(&movies[count], sizeof(Movie), 1, fptr) == 1)
    {
        count++;
    }

    printf("Available Movies:\n");
    for (int i = 0; i < count; i++)
    {
        printf("%d. Title: %s\n", i + 1, movies[i].title);
        printf("   Genre: %s\n", movies[i].genre);
        printf("   Year: %d\n", movies[i].year);
        printf("   Director: %s\n", movies[i].director);
        printf("   Language: %s\n", movies[i].language);
        printf("===============================\n");
    }

    int searchOption;
    printf("Select search option:\n");
    printf("1. Search by index\n");
    printf("2. Search by movie title\n");
    printf("Enter your choice: ");
    scanf("%d", &searchOption);
    getchar();

    int foundIndex = -1;
    char searchTitle[100];

    switch (searchOption)
    {
    case 1:
        printf("Enter the movie index to edit: ");
        int index;
        scanf("%d", &index);
        foundIndex = index - 1;
        break;

    case 2:
        printf("Enter the movie title to edit: ");
        fgets(searchTitle, sizeof(searchTitle), stdin);

        for (int i = 0; i < count; i++)
        {
            if (strcmp(movies[i].title, searchTitle) == 0)
            {
                foundIndex = i;
                break;
            }
        }
        break;

    default:
        printf("Invalid search option.\n");
        free(movies);
        return;
    }

    if (foundIndex == -1)
    {
        printf("Movie not found.\n");
        free(movies);
        return;
    }

    printf("Enter new details for the movie:\n");

    printf("Title: ");
    fgets(movies[foundIndex].title, sizeof(movies[foundIndex].title), stdin);

    printf("Genre: ");
    fgets(movies[foundIndex].genre, sizeof(movies[foundIndex].genre), stdin);

    printf("Year: ");
    scanf("%d", &movies[foundIndex].year);
    getchar();

    printf("Director: ");
    fgets(movies[foundIndex].director, sizeof(movies[foundIndex].director), stdin);

    printf("Language: ");
    fgets(movies[foundIndex].language, sizeof(movies[foundIndex].language), stdin);

    rewind(fptr);
    fwrite(movies, sizeof(Movie), count, fptr);

    printf("Movie details updated successfully.\n");

    free(movies);
}


