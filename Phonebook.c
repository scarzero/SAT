/* It will only run in Windows machine
To run the code in other machine please remove #include <windows.h>
and system (); and replace fflush(); with your supported command to clear the buffer in memory 
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>


void addperson(FILE *fptr);
void delelteone(FILE *fptr);
void update(FILE * fptr);
void searchandprint(FILE *fptr);
int search(FILE *fptr,char name[]);
void displayall(FILE * fptr);
void deleteall(FILE * fptr);
int count(FILE *fptr);


struct
{
    char fname[256];
    char lname[256];
    char number[256];
    char gender[256];
    char email[256];
    char birthdate[256];
    char address[256];
} contact,temp;
int main()
{
    /*  for color
    0 = Black       8 = Gray
    1 = Blue        9 = Light Blue
    2 = Green       A = Light Green
    3 = Aqua        B = Light Aqua
    4 = Red         C = Light Red
    5 = Purple      D = Light Purple
    6 = Yellow      E = Light Yellow
    7 = White       F = Bright White */
    system("color E0");
    system("cls");
    FILE *fptr;
    fptr=fopen("phonebook.txt","r+");
    if(fptr==NULL)
    {
        fptr=fopen("phonebook.txt","w+");
        if(fptr==NULL)
        {
            printf("Error in opening File\n");
            exit(1);
        }
    }

    while(1) //defining menu
    {
        system("cls"); //clearing the console
        printf("\t\t\t\t   Phonebook management System written in C\n\n");
        printf("\t\t1.Add new contact\n");
        printf("\t\t2.Update the contact details\n");
        printf("\t\t3.Display all saved contacts\n");
        printf("\t\t4.Delete a contact\n");
        printf("\t\t5.Search for a Contact\n");
        printf("\t\t6.See total number of contacts saved\n");
        printf("\t\t7.Exit PhoneBook\n");
        printf("\t\t8.Delete all the record\n\n\n\n");

        printf("Choose an option  ");
        fflush(stdin);
        switch(getch())
        {
        case '1':
            addperson(fptr);
            break;
        case '2':
            update(fptr);
            break;
        case '3':
            displayall(fptr);
            break;
        case '4':
            delelteone(fptr);
            break;
        case '5':
            searchandprint(fptr);
            break;
        case '6':
            system("cls");
            printf("\n\nThere are %d contacts saved in this phonebook\n",count(fptr));
            printf("\nPress Any key\n");
            break;
        case '7':
            fclose(fptr);
            exit(0);
            break;
        case '8':
            deleteall(fptr);
            break;


        default:
            printf("\nError input\n");
            system("cls");
            printf("Please Enter your choice correctly next time(1 - 8 only)");

        }

        getchar();


    }



}

void addperson(FILE *fptr)  //function for inputing the contact from the user
{
    system("cls");
    fflush(stdin);
    fseek(fptr,0,2);  //taking pointer to the top position
    /*The fseek() function change the current file position that is associated with stream to a new location within the file.*/
    int c;
    printf("\nDo you want to add contact to your phonebook?\n");
    printf("Press  1 to confirm \n");
    printf("Press 2 to Go back to Main Menu\n");
    scanf("%d",&c);
    if(c==1)
    {
        system("cls");
        printf("\n1.First Name(Required):");
        fflush(stdin);
        gets(contact.fname);
        printf("\n2.Last Name:");
        fflush(stdin);
        gets(contact.lname);
        printf("\n3.Mobile Number:");
        fflush(stdin);
        gets(contact.number);
        while(1)
        {
            if(strlen(contact.number)<=7 || strlen(contact.number)>=20)
            {
                printf("Invalid Phone Number");
                printf("\n3.Mobile Number:");
                fflush(stdin);
                gets(contact.number);
            }
            else
            {
                break;
            }

        }
        printf("\n4.Gender:");
        fflush(stdin);
        gets(contact.gender);
        printf("\n5.Email:");
        fflush(stdin);
        gets(contact.email);
        printf("\n6.Brithdate:");
        fflush(stdin);
        gets(contact.birthdate);
        printf("\n7.Address:");
        fflush(stdin);
        gets(contact.address);

        fwrite(&contact,sizeof(contact),1,fptr);  //writing the data into file
        printf("\nYour contact has been saved\n");
        printf("\nPress Enter \n");
    }
    else
    {
        return;
    }
}

void displayall(FILE *fptr)
{
    system("cls");
    rewind(fptr);

    while(fread(&contact,sizeof(contact),1,fptr)==1)
    {
        printf("\n***********************************\n");
        printf("Contact details of %s %s \n",contact.fname,contact.lname);
        printf("\n1.First Name:%s",contact.fname);
        printf("\n2.Last Name:%s",contact.lname);
        printf("\n3.Mobile Number:%s",contact.number);
        printf("\n4.Gender:%s",contact.gender);
        printf("\n5.Email:%s",contact.email);
        printf("\n6.Brithdate:%s",contact.birthdate);
        printf("\n7.Address:%s\n",contact.address);
        printf("\n***********************************\n");

    }

}
void delelteone(FILE *fptr)
{

    system("cls");
    FILE *temporary;
    char name[100];

    printf("Enter the First name whose contact details to be deleted:");
    fflush(stdin);
    gets(name);
    if(search(fptr,name)==0)
    {
        /*printf("\nPress 1 to search again\n");
        printf("\nPress 2 to return to main menu\n");
        switch (getch())
        {
        case '1':
        delelteone(fptr);

            break;

        case '2':
            return;
            break;
        }*/
        return;
    }

    temporary=fopen("temporary.txt","a+");   //creating the temp file for deleting the record
    if(temporary==NULL)
    {
        printf("Error in opening file\n");
        exit(0);
    }
    rewind(fptr);   //taking  pointer to the top


    while(fread(&contact,sizeof(contact),1,fptr)==1)
    {
        if(strcmp(name,contact.fname)!=0)
        {
            fwrite(&contact,sizeof(contact),1,temporary);
            //writing the data on temp the file;

        }

    }
    fclose(fptr);//closing the file
    fclose(temporary);
    remove("phonebook.txt");
    rename("temporary.txt","phonebook.txt");
    //renaming the temp file with original file
    printf("Your contact %s has been deleted successfully\n",name);
    fptr=fopen("phonebook.txt","a+");


}
void update(FILE *fptr)
{
    system("cls");
    char name[100];
    long size=sizeof(contact);
    fflush(stdin);
    int a;
    printf("Do you want to edit one of your contact?\n");
    printf("Press  1 to confirm \n");
    printf("Press 2 to Go back \n");
    scanf("%d",&a);

    if(a==1)
    {
        system("cls");
        printf("Enter the first name of the contact you want to Update:");
        fflush(stdin);
        gets(name);
        if(search(fptr,name)==1)
        {
            fflush(stdin);
            printf("\n1.First Name:");
            fflush(stdin);
            gets(contact.fname);
            printf("\n2.Last Name:");
            fflush(stdin);
            gets(contact.lname);
            printf("\n3.Mobile Number:");
            fflush(stdin);
            gets(contact.number);
            printf("\n4.Gender:");
            fflush(stdin);
            gets(contact.gender);
            printf("\n5.Email:");
            fflush(stdin);
            gets(contact.email);
            printf("\n6.Brithdate:");
            fflush(stdin);
            gets(contact.birthdate);
            printf("\n7.Address:");
            fflush(stdin);
            gets(contact.address);
            printf("\n\nYour contact %s has been modified\n\n",name);

        }
        else
        {
            printf("\nNo match found for %s\n",name);
        }
        // fseek take 3 arguments //fseek(file pointer,offset,position) //
        fseek(fptr,-size,1);  //deleting the previous record
        fwrite(&contact,sizeof(contact),1,fptr);  //writing the new record


    }
    else
    {
        return;
    }

}


void searchandprint(FILE *fptr)//search the record of particular person
{
    system("cls");
    char name[100];
    int flag=0;
    printf("Enter the first name you want to search: ");
    fflush(stdin);
    gets(name);
    rewind(fptr);   //taking pointer to the top of file
    while(fread(&contact,sizeof(contact),1,fptr)==1)
    {
        if(strcmp(name,contact.fname)==0)
        {
            printf("\n***********************************\n");
            printf("Contact details of %s %s \n",contact.fname,contact.lname);
            printf("\n1.First Name:%s",contact.fname);
            printf("\n2.Last Name:%s",contact.lname);
            printf("\n3.Mobile Number:%s",contact.number);
            printf("\n4.Gender:%s",contact.gender);
            printf("\n5.Email:%s",contact.email);
            printf("\n6.Brithdate:%s",contact.birthdate);
            printf("\n7.Address:%s\n",contact.address);
            printf("\n***********************************\n");
            flag=1;
            break;
        }
    }
    if(flag==0)
    {
        printf("\n\nMatch not found\n\n");
    }
}



int search(FILE *fptr,char name[])
{
    int flag=0;

    rewind(fptr);
    while(fread(&contact,sizeof(contact),1,fptr)==1)
    {
        if(strcmp(name,contact.fname)==0)
        {
            flag=1;

            break;
        }

    }
    if(flag==0)
    {
        printf("\nMatch not found\n");
        printf("\nPress Any Key to Return to main menu\n");
    }

    return flag;
}
int count(FILE * fptr)   //count the number of records
{
    rewind(fptr);
    int count=0;
    while(fread(&contact,sizeof(contact),1,fptr)==1)
    {
        count++;
    }
    return count;



}

void deleteall(FILE *fptr)
{
    system("cls");
    printf("Do you want to delete everything ?\n");
    printf("Press  1 to confirm \n");
    printf("Enter Any to Go back \n");
    fflush(stdin);
    if(getch()=='1')
    {
        system("cls");
        printf("\n\nAll the contact deleted successfully\n\n");
        printf("\nPress Any to Go back \n");
        fptr=fopen("phonebook.txt","w");

    }

    else
    {
        fflush(stdin);
        return;
    }
}
