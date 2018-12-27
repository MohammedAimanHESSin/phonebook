#include <stdio.h> #include <stdlib.h>  #include <string.h> #include <conio.h>  #include "project.h"

/** Declarations of Structures **/
typedef struct
{
    char day[16];
    char month[32];
    char year[128];
} birth;
typedef struct
{
    char first_name[256];
    char last_name[256];
    birth BD;
    char adress[256];
    char email[256];
    char mob_num[256];
} cont;

/**Global Variable**/
cont arr[256];
int counter=0;
int flag_s =1 ;

/***** Menu Functions ****/

/******************************************** AUTOMATIC LOAD FUNCTION *******************************************/
void LOAD ()
{
    system("cls");
    FILE *fRptr ;
    fRptr = fopen("phonebook.txt","r");
    if (fRptr == NULL)
    {
        printf("\n");
    }
    else
    {

        while(!feof(fRptr))
        {
            /*** loading records from file **/
            fscanf(fRptr,"%[^,],",arr[counter].last_name);
            fscanf(fRptr,"%[^,],",arr[counter].first_name);
            fscanf(fRptr,"%[^-]-",arr[counter].BD.day);
            fscanf(fRptr,"%[^-]-",arr[counter].BD.month);
            fscanf(fRptr,"%[^,],",arr[counter].BD.year);
            fscanf(fRptr,"%[^,],",arr[counter].adress);
            fscanf(fRptr,"%[^,],",arr[counter].email);
            fscanf(fRptr,"%s\n",arr[counter].mob_num);
            counter++;
        }
        fclose(fRptr);
    }
}


/******************************************* (1) ADD FUNCTION *******************************************/

void ADD()
{

    system("cls");
    int n ;
    printf("\n\nHow many contacts do you want to ADD ? ");
    scanf("%d",&n);
    int i;
    for( i=0 ; i<n; i++)
    {
        printf("\nEnter the last name of contact No.%d:",(i+1));
        int check_ln;
        do
        {
            scanf(" %[^\t\n]s",arr[counter].last_name);
            check_ln = validate_string((arr[counter].last_name));
        }
        while(!check_ln);
        printf("\nEnter the first name of contact No.%d:",(i+1));
        int check_fn;
        do
        {
            scanf(" %[^\t\n]s",arr[counter].first_name);
            check_fn =validate_string((arr[counter].first_name));
        }
        while(!check_fn);
        printf("\nEnter the birth date of contact No.%d:\n",(i+1));
        printf("day: ");
        int check_d;
        do
        {
            scanf(" %s",arr[counter].BD.day);
            check_d = validate_day(arr[counter].BD.day);
        }
        while(!check_d);
        printf("month: ");
        int check_mon;
        do
        {
            scanf(" %s",arr[counter].BD.month);
            check_mon = validate_month(arr[counter].BD.month);
        }
        while(!check_mon);
        printf("year: ");
        int check_year,numofdig;
        do
        {
            scanf(" %s",arr[counter].BD.year);
            numofdig=count(atoi(arr[counter].BD.year));
            check_year = validate_year(arr[counter].BD.year,numofdig);
        }
        while(!check_year);
        printf("\nEnter the address of  contact No.%d:",(i+1));
        scanf(" %[^\t\n]s",arr[counter].adress);
        printf("\nEnter the email of  contact No.%d:",(i+1));
        int check_e;
        do
        {
        scanf(" %s",arr[counter].email);
        check_e=isValid(arr[counter].email);
        }while(check_e!=1);

        printf("\nEnter the mobile number of  contact No.%d :",(i+1));
        int check_m;
        do
        {
            scanf("%s",arr[counter].mob_num);
            check_m = validate_num(arr[counter].mob_num);
        }
        while(!check_m);
        printf("\n\n\n______________________________________________________\n\n");
        counter++;
    }
    flag_s=0;
    WAIT();
}

/******************************************* (2)SORT FUNCTION *******************************************/
void SORT()
{
    system("cls");
    /** options menu **/
    printf("\n\tChoose WHat To Sort With .... \n");
    printf("\n\n\t\t*** OPTIONS ***\n\n");
    printf("\t\t [A] ALL \n");
    printf("\t\t [F] FIRST NAME \n");
    printf("\t\t [L] LAST NAME \n");
    printf("\t\t [M] MOBILE NUMBER \n");
    printf("\t\t [D] DATE OF BIRTH \n");

    switch(getch())
    {
    case 'A' :
    case 'a' :
        sort_ALL();
        printf("\n\n\tSORTED COMPLETED\n\n");
        WAIT();
        break;
    case 'F' :
    case 'f':
    {
        int i ;
        for (i=0 ; i<counter-1 ; i++)
        {
            int j;
            for (j=0 ; j<counter-i-1; j++)
            {
                sort_first (j );
            }
        }
        printf("\n\n\tSORTED COMPLETED\n\n");
        WAIT();
        break;
    }
    case 'L':
    case 'l':
    {
        int i;
        for (i=0 ; i<counter-1 ; i++)
        {
            int j;
            for (j=0 ; j<counter-i-1; j++)
            {
                sort_last (j );
            }
        }
        printf("\n\n\tSORTED COMPLETED\n\n");
        WAIT();
        break;
    }
    case 'M':
    case 'm':
    {
        int i ;
        for ( i=0 ; i<counter-1 ; i++)
        {
            int j;
            for ( j=0 ; j<counter-i-1; j++)
            {
                sort_mob (j );
            }
        }
        printf("\n\n\tSORTED COMPLETED\n\n");
        WAIT();
        break;
    }
    case 'D' :
    case 'd' :
    {
        int i;
        for (i=0 ; i<counter-1 ; i++)
        {
            int j;
            for (j=0 ; j<counter-i-1; j++)
            {
                sort_date(j);
            }
        }

        printf("\n\n\tSORTED COMPLETED\n\n");
        WAIT();
        break;
    }
    default:
        printf("\n \tInvalid choice!\n");
        break;
    }
    flag_s=0;
}

/******************************************* (3)MODIFY FUNCTION *******************************************/

void MODIFY ()
{
    system("cls");
    char target[128] ;
    puts("\nEnter last name of the contact you want to Modify in : ");
    scanf("%s",target);
    int j=0 ;
    int a[100];
    int flag_mod=0 ;
    int fflag,i;
    int flag_h=1;
    for (i =0; i < counter; i++)
    {
        if (strcasecmp(target,arr[i].last_name)==0)
        {
            flag_mod=1;
            if(flag_h==1)
            {
                printf("\nContacts with this last name [%s] : \n\n ",target);
                flag_h--;
            }
            printf("\n\tNo.%d\n",i);
            printf("last name is : %s \n",arr[i].last_name);
            printf("first name is :%s \n",arr[i].first_name);
            printf("Date of birth is %s-%s-%s \n",arr[i].BD.day,arr[i].BD.month,arr[i].BD.year);
            printf("address is : %s\n",arr[i].adress);
            printf("email is :%s \n",arr[i].email);
            printf("mobile number is : %s\n",arr[i].mob_num);
            printf("\n");
            a[j]=i;
            j++;
        }
    }

    /** if user enter an invalid last name **/
    if (flag_mod==0)
    {
        printf("\nINvalid last name !\n");
        WAIT();
        return;
    }

    /** if user search for one person with this last name **/
    if(j==1)
    {
        int choice0;
        do
        {
            fflag=1;
            printf("\n*** Enter what to modify ***\n\n");
            printf( "1:Last name\n2:First name\n3:BirthDate\n4:Address\n5:E-mail\n6:Mobile number\n7:Nothing To Modify\n" );
            scanf("%d",&choice0);

            switch(choice0)
            {
            case 1 :
                printf("Enter new last name :");
                flag_s=0;
                int check_ln;
                do
                {
                    scanf(" %[^\t\n]s",arr[a[0]].last_name);
                    check_ln = validate_string((arr[a[0]].last_name));
                }
                while(!check_ln);

                break;
            case 2 :
                printf("Enter new first name :");
                int check_ln2;
                do
                {
                    scanf(" %[^\t\n]s",arr[a[0]].first_name);
                    check_ln2 = validate_string((arr[a[0]].first_name));
                }
                while(!check_ln2);
                flag_s=0;
                break;
            case 3 :
                flag_s=0;
                printf("Enter new birth date :\n");
                printf("Enter new birth [day] :");
                int check_d;
                do
                {
                    scanf(" %s",arr[a[0]].BD.day);
                    check_d = validate_day(arr[a[0]].BD.day);
                }
                while(!check_d);
                printf("Enter new birth [month] :");
                int check_mon;
                do
                {
                    scanf(" %s",arr[a[0]].BD.month);
                    check_mon = validate_month(arr[a[0]].BD.month);
                }
                while(!check_mon);
                printf("Enter new birth [year] :");
                int check_year,numofdig;
                do
                {
                    scanf(" %s",arr[a[0]].BD.year);
                    numofdig=count(atoi(arr[a[0]].BD.year));
                    check_year = validate_year(arr[a[0]].BD.year,numofdig);
                }
                while(!check_year);

                break;
            case 4 :
                printf("Enter new address :");
                scanf("%s",arr[a[0]].adress);
                flag_s=0;

                break;
            case 5 :
                printf("Enter new email :");
                scanf("%s",arr[a[0]].email);
                flag_s=0;

                break;
            case 6 :
                printf("Enter new mobile number :");
                int check_m;
                do
                {
                    scanf("%s",arr[a[0]].mob_num);
                    check_m = validate_num(arr[a[0]].mob_num);
                }
                while(!check_m);
                flag_s=0;
                break;

            case 7 :
                printf("\nyou are quiting from modify !\n");
                WAIT();

                return;
            default:
                printf("\nInvalid choice!\n");
                break;
            }
        }
        while (choice0 != 7);
    }

    /**if there are many persons with same last name **/
    int k;
    printf("what is contact number does you want to Modify in :");
    scanf("%d",&k);
    int n ;
    for ( n=0; n<j; n++)
    {
        /**user enter a valid person number**/
        if(a[n]==k)
        {
            int choice1;
            do
            {
                fflag=1;
                printf("\n*** Enter what to modify ***\n\n");
                printf( "1:Last name\n2:First name\n3:BirthDate\n4:Address\n5:E-mail\n6:Mobile number\n7:END MODIFYING\n" );
                scanf("%d",&choice1);

                switch(choice1)
                {
                case 1 :
                    printf("enter new last name :");
                    flag_s=0;
                    int check_ln;
                    do
                    {
                        scanf(" %[^\t\n]s",arr[k].last_name);
                        check_ln = validate_string((arr[k].last_name));
                    }
                    while(!check_ln);


                    break;
                case 2 :
                    printf("enter new first name :");
                    int check_ln3;
                    do
                    {
                        scanf(" %[^\t\n]s",arr[k].first_name);
                        check_ln3 = validate_string((arr[k].first_name));
                    }
                    while(!check_ln3);

                    flag_s=0;

                    break;
                case 3 :
                    flag_s=0;
                    printf("enter new birth date :\n");
                    printf("enter new birth [day] :");
                    int check_d;
                    do
                    {
                        scanf(" %s",arr[k].BD.day);
                        check_d = validate_day(arr[k].BD.day);
                    }
                    while(!check_d);
                    printf("enter new birth [month] :");
                    int check_mon;
                    do
                    {
                        scanf(" %s",arr[k].BD.month);
                        check_mon = validate_month(arr[k].BD.month);
                    }
                    while(!check_mon);
                    printf("enter new birth [year] :");
                    int check_year,numofdig;
                    do
                    {
                        scanf(" %s",arr[k].BD.year);
                        numofdig=count(atoi(arr[k].BD.year));
                        check_year = validate_year(arr[k].BD.year,numofdig);
                    }
                    while(!check_year);


                    break;
                case 4 :
                    printf("enter new address :");
                    scanf("%s",arr[k].adress);
                    flag_s=0;

                    break;
                case 5 :
                    printf("enter new email :");
                    scanf("%s",arr[k].email);
                    flag_s=0;

                    break;
                case 6 :
                    printf("enter new mobile number :");
                    int check_m1;
                    do
                    {
                        scanf("%s",arr[k].mob_num);
                        check_m1 = validate_num(arr[k].mob_num);
                    }
                    while(!check_m1);
                    flag_s=0;
                    flag_s=0;

                    break;
                case 7 :
                    printf("\nyou are quiting from modify !\n");
                    WAIT();
                    return;
                default:
                    printf("\nInvalid choice!\n");
                    break;
                }
            }
            while (choice1 != 7);
        }
        else
            continue;
    }

    /**user enter a invalid person number**/
    if(fflag!=1)
    {
        printf("\n\n INvalid choice ! \n ");
        WAIT();
        return;
    }
}
/******************************************* (4) DELETE *******************************************/

void DELETE()
{
    system("cls");
    char target[128] ;
    puts("\nEnter last name of the contact you want to delete : ");
    scanf("%s",target);
    int flag_dele=0;
    int j =0;
    int a[100];
    int flag_h=1;
    int r=1;
    int i;
    for (i =0; i < counter; i++)
    {
        if ((strcasecmp(target,arr[i].last_name)==0))
        {
            flag_dele =1;
            if(flag_h==1)
            {
                printf("\nContacts with this last name [%s] : \n\n ",target);
                flag_h--;
            }
            printf("\n\tNo.%d\n",i);
            printf("last name is :%s \n",arr[i].last_name);
            printf("first name is : %s \n",arr[i].first_name);
            printf("Date of birth is %s-%s-%s \n",arr[i].BD.day,arr[i].BD.month,arr[i].BD.year);
            printf("address is : %s\n",arr[i].adress);
            printf("email is :%s \n",arr[i].email);
            printf("mobile number is : %s\n",arr[i].mob_num);
            printf("\n");
            a[j]=i;
            j++;
        }
        int r=counter ;
    }
    if (flag_dele==1)
    {
        int k;
        printf("what is contact number does you want to delete : ");
        scanf("%d",&k);
        int n;
        for (n=0; n<j; n++)
        {
            if(a[n]==k)
            {
                arr[k]=arr[counter-1];
                counter--;
                r--;
                flag_s=0;
                printf("\n\n\t DELETED SUCCESSFULLY !\n");
                break ;
            }
        }

    }
    else
    {
        printf("\n INvalid LAST NAME !\n ");
    }

    if (r==1)
        printf("\nINvalid choice !\n");
    WAIT();
}

/*****************************************(5) PRINT FUNCTION *******************************************/
void PRINT()
{
    system("cls");
    sort_ALL();
    //bubble_sort();
    printf("\n\n\t Printing entire Directory In sorted Order \n\n");
    int i;
    for (i=0 ; i<counter; i++)
    {
        printf("\tNo.%d\n",i+1);
        printf("last name is :%s \n",arr[i].last_name);
        printf("first name is : %s \n",arr[i].first_name);
        printf("Date of birth is :%s-%s-%s \n",arr[i].BD.day,arr[i].BD.month,arr[i].BD.year);
        printf("address is : %s\n",arr[i].adress);
        printf("email is :%s \n",arr[i].email);
        printf("mobile number is : %s \n",arr[i].mob_num);
        printf("\n");


    }
    printf("\n\n\n______________________________________________________\n\n");
    printf(" \n\n End of Printing \n\n");
    WAIT();
}
/******************************************* (6)SEARCH FUNCTION *******************************************/
void SEARCH()
{
    system("cls");
    /** options menu **/
    printf("\n\t*** Choose WHat To Search With ***\n");
    printf("\n\n\t\t*** OPTIONS ***\n\n");
    printf("\t\t [S] Simple search \n");
    printf("\t\t [M] Multi search \n");
    switch(getch())
    {
    case 'S':
    case 's':
        simple_search();
        break;
    case 'M':
    case 'm':
        multi_search();
        break;
    default:
        printf("\n \tInvalid choice!\n");
        break;
    }
    WAIT();
}

/******************************************* (7)SAVE FUNCTION *******************************************/

void SAVE()
{
    system("cls");
    FILE*fptr;
    fptr=fopen("phonebook.txt","w+");
    fseek(fptr,0,SEEK_SET);
    printf("%d",counter);
    int i;
    for(i=0; i<counter; i++)
    {

        fprintf(fptr,"%s,%s,%s-%s-%s,%s,%s,%s\n",arr[i].last_name,arr[i].first_name,arr[i].BD.day,arr[i].BD.month,arr[i].BD.year,
                arr[i].adress,arr[i].email,arr[i].mob_num);
    }
    fclose(fptr);
    flag_s=1;
    system("cls");
    printf("\n\n\t ** Saved successfully !** \n");
    char ch ;
    while ((ch = getchar()) != '\n' && ch != EOF) ;
    printf("\n\nPress ENTER to Continue  .....");
    while ((ch = getchar()) != '\n' && ch != EOF) ;
}

/******************************************* (8) EXIT FUNCTION *************************************************************************/

void Exit ()
{
    system("cls");
    if (flag_s==1)
    {
        printf("\n \n \t Quitting program!\n\n");
        exit(0);
    }
    else
    {
        printf("\n\tDo you want to save changes you made?\n");
        printf("\n\n\t\t*** OPTIONS ***\n\n");
        printf("\t\t [Y] YES \n");
        printf("\t\t [N] NO \n");
        printf("\t\t [B] BACK TO MAIN MENU \n");
        switch(getch())
        {
        case 'y':
        case 'Y':
            SAVE();
            printf("\n \n \t Quitting program!\n\n");
            exit(0);

        case 'n':
        case 'N':
            printf("\n \n \t Quitting program!\n\n");
            exit(0);

        case 'b':
        case 'B':
            system("cls");
            Load_menu();
            break;

        default:
            printf("\n \tInvalid choice!\n");
            char ch ;
            break ;
        }
    }


}
/******************************************* SEARCHING OPTIONS *****************************************************************/

/**Simple search**/
void simple_search()
{
    char target[100] ;
    system("cls");
//char str[20];
    printf("\nEnter the last name to search:");
    //fgets(str, 20, stdin);
    //  gets(target.last_name);
    //puts(target.last_name);
    scanf("%s",target);

    int j=1,k=0,i,flag_ser=0, num_found=0;
    int index[counter];
    for (i =0; i < counter; i++)
    {
        if (strcasecmp(target,arr[i].last_name)==0)
        {
            index[k++]=i;
            num_found ++ ;
            flag_ser = 1;
        }
    }
    if ( flag_ser==0|| num_found==0)
        printf("\n\n ** This name doesn't exist in directory !** \n");
    else
    {
        system("cls");
        printf("\n\t ** RESULT OF SEARCHING ** \n");
        for( j =0 ; j < num_found ; j ++)
        {
            printf("\n\tNo.%d\n",j+1);
            printf("last name is :%s \n",arr[index[j]].last_name);
            printf("first name is : %s \n",arr[index[j]].first_name);
            printf("Date of birth is %s-%s-%s \n",arr[index[j]].BD.day,arr[index[j]].BD.month,arr[index[j]].BD.year);
            printf("address is : %s\n",arr[index[j]].adress);
            printf("email is :%s \n",arr[index[j]].email);
            printf("mobile number is : %s\n",arr[index[j]].mob_num);
            printf("\n");
        }
        printf("\n\t ** TOTAL FOUND IS [%d] ** \n", num_found);
    }
}
/**Multi search**/

void multi_search()
{
    system("cls");
    cont target ;
    int index[counter]; /*array to save index of result*/     char str [100];
    printf("\t *** Press [ Enter ] to skip search by any field *** \n");
    printf("\nEnter the last name to search:");
    fgets(str, 100, stdin);
    gets(target.last_name);
    printf("\nEnter the first name to search:");
    gets(target.first_name);
    printf("\nEnter the birth date to search\n");
    printf("day: ");
    gets(target.BD.day);
    printf("month: ");
    gets(target.BD.month);
    printf("year: ");
    gets(target.BD.year);
    printf("\nEnter the mobile number search:");
    gets(target.mob_num);
    printf("\nEnter the address to search: ");
    gets(target.adress);
    printf("\nEnter the email to search:");
    gets(target.email);
    /**verify that all entry isn't null **/
    if (cmp_null(target.last_name)&&cmp_null(target.first_name)&&cmp_null(target.BD.day)&&cmp_null(target.BD.month)&&cmp_null(target.BD.year)&&cmp_null(target.adress)&&cmp_null(target.email)&&cmp_null(target.mob_num))
    {
        printf("\n ** No data to search with  **\n");
    }
    else
    {
        int j=1,k=0,i,flag_ser=0, num_found=0;
        int index[counter];
        for (i =0; i < counter; i++)
        {
            /**searching...**/
            if (cmp_str(target.last_name,arr[i].last_name)&&cmp_str(target.first_name,arr[i].first_name)&&cmp_str(target.BD.day,arr[i].BD.day)&&cmp_str(target.BD.month,arr[i].BD.month)&&cmp_str(target.BD.year,arr[i].BD.year)&&cmp_str(target.adress,arr[i].adress)&&cmp_str(target.email,arr[i].email)&&cmp_str(target.mob_num,arr[i].mob_num))
            {
                index[k++]=i;
                num_found ++ ;
                flag_ser = 1;
            }
        }
        if ( flag_ser==0|| num_found==0)
            printf("\n\t** This name doesn't exist in directory ! **\n");
        else
        {
            system("cls");
            printf("\n\t ** RESULT OF SEARCHING ** \n");
            for( j =0 ; j < num_found ; j ++)
            {
                printf("\n\tNo.%d\n",j+1);
                printf("last name is :%s \n",arr[index[j]].last_name);
                printf("first name is : %s \n",arr[index[j]].first_name);
                printf("Date of birth is %s-%s-%s \n",arr[index[j]].BD.day,arr[index[j]].BD.month,arr[index[j]].BD.year);
                printf("address is : %s\n",arr[index[j]].adress);
                printf("email is :%s \n",arr[index[j]].email);
                printf("mobile number is : %s\n",arr[index[j]].mob_num);
                printf("\n");
            }
            printf("\n\t ** TOTAL FOUND IS [%d] ** \n", num_found);
        }
    }
}
/******************************************* SORTING OPTIONS *****************************************************************/

//comparing last names
int sort_last ( int j )
{
    if((strcasecmp(arr[j].last_name,arr[j+1].last_name)>0))
    {
        cont temp ;
        temp = arr[j];
        arr[j]=arr[j+1];
        arr[j+1]=temp;
        return 1 ;
    }
    else   if((strcasecmp(arr[j].last_name,arr[j+1].last_name))==0)
    return 0 ;
    else return -1;
}

/**comparing first names**/
int  sort_first (int j )
{
    if (strcasecmp(arr[j].first_name,arr[j+1].first_name)>0)
    {
        cont temp ;
        temp = arr[j];
        arr[j]=arr[j+1];
        arr[j+1]=temp;
        return 1;
    }
    else if ((strcasecmp(arr[j].first_name,arr[j+1].first_name)==0))
    return 0 ;
    else return -1;

}

/**comparing mobile numbers**/
int  sort_mob (int j )
{
    if (strcasecmp(arr[j].mob_num,arr[j+1].mob_num)>0)
    {
        cont temp ;
        temp = arr[j];
        arr[j]=arr[j+1];
        arr[j+1]=temp;
        return 1;

    }
    else if ((strcasecmp(arr[j].mob_num,arr[j+1].mob_num))==0)
    return 0 ;
    else return -1;
}
/**comparing date of birth**/
int sort_date(int j)

{
    if((strcasecmp(arr[j].BD.year,arr[j+1].BD.year))>0)
    {
        cont temp ;
        temp = arr[j];
        arr[j]=arr[j+1];
        arr[j+1]=temp;
        return 1 ;
    }
    else if((strcasecmp(arr[j].BD.year,arr[j+1].BD.year)==0))
    {

        if((strcasecmp(arr[j].BD.month,arr[j+1].BD.month))>0)
        {
            cont temp ;
            temp = arr[j];
            arr[j]=arr[j+1];
            arr[j+1]=temp;
            return 1 ;
        }
        else if((strcasecmp(arr[j].BD.month,arr[j+1].BD.month))==0)
        {
            if((strcasecmp(arr[j].BD.day,arr[j+1].BD.day))>0)
            {
                cont temp ;
                temp = arr[j];
                arr[j]=arr[j+1];
                arr[j+1]=temp;
                return 1 ;
            }

        }
        else return -1 ;

    }
    else return -1;
}
/** sorting by all data **/
void sort_ALL()
{
    int i,flag_sort=1;
    for (i=0 ; i <counter-1 ; i++)
    {
        int j ;

        for (j=0 ; j<counter-i-1; j++)
        {

            if (sort_last(j))
                printf("\t");
            else if (sort_first(j))
                printf("\t");
            else if  (sort_mob(j))
                printf("\t");
            else if (sort_date(j))
                printf(" \t");

        }
    }
}

/******************************************* VALDITION FUNCTIONS *************************************************************************/
#include <stdio.h>
#include <stdlib.h>


int isValid (char s[])
{
    int length=strlen(s), ind1=0, ind2=0, ind3=0;

    if ( (s[0]<'a') || (s[0]>'z') ){printf("write correct email\n");return 0;}
    else
    {
    for (int i=1;i<length;i++)
      {
        if (s[i]=='@')
        {
            //printf("%c",s[i]);
            ind1=i+1;
            break;
        }
        else
            if (( (s[i]<'a') || (s[i]>'z') )) {printf("write correct email\n");return 0;}

       }
    }


    for (int j=ind1;j<length;j++)
    {
        if (s[j]=='.')
        {
            return 1;
        }
        else if  ((s[j]<'a') || (s[j]>'z') ) {printf("write correct email\n");return 0;}
    }
    printf("write correct email\n");
    }

int validate_day(char* number)
{
    int flag_m=1;

    if ( atoi(number)>31 || atoi(number)<=0 || strlen(number)>2)
    {
        printf("[Please Re-enter a right Day !] :");
        flag_m=0;
    }

    return flag_m;
}


int validate_month(char* number)
{
    int flag_m=1;
    if ( atoi(number)>12 || atoi(number)<=0|| strlen(number)>2)
    {

        printf("[Please Re-enter a right Month !] :");
        flag_m=0;
    }


    return flag_m;
}

int validate_year(char* number,int numofdig)
{
    int flag_m=1;
    if ((numofdig) != 4||atoi(number)<=0|| strlen(number)>4)
    {

        printf("[Please Re-enter a right Year !] :");
        flag_m=0;
    }


    return flag_m;
}


int validate_string(char *string)
{
    int flag_y ;
    int k ;
    for(k=0; k<strlen(string); k++)
    {
        if((string[k]>=97&&string[k]<=122)||(string[k]>=65&&string[k]<=90))
            flag_y = 1;
        else
        {
            flag_y =0;
            printf(" [Please Re-enter a right name ! ]:");
            break;
        }

    }
    return flag_y;
}

int validate_num(char *number)
{

    int i,flag_m=1;

    for (i=0; i<strlen (number); i++)
    {
        if ( !(isdigit(number[i])) || number[0]==45)
        {
            printf("[Please Re-enter a right mobile number !] : ");
            flag_m=0;
            break;
        }
    }

    return flag_m;
}

/*******************************************************************************************************************************/


/** functions to count digits **/
int count(int number)
{
    int numofdig=0 ;
    while (number!=0)
    {
        number= number/10;
        numofdig++;
    }
    return numofdig ;

}
/** waiting function **/
void WAIT()
{
    char ch ;
    while ((ch = getchar()) != '\n' && ch != EOF) ;
    printf("\n\nPress ENTER to Back to Main Menu ......");
    while ((ch = getchar()) != '\n' && ch != EOF) ;
}
/** comparing function **/
int cmp_str(char* target,char* string)
{
    if ((target[0]=='\0')||(strcasecmp(target,string)==0))
    {
        return 1 ;
    }

    else
        return 0;
}

int cmp_null(char* target)
{
    if ((target[0]=='\0'))
    {
        return 1 ;
    }
    return 0  ;
}
