#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct items{
    char item[20];
    float price;
    int qty;
};

struct orders{
    char customer[50];
    char date[50];
    int numOfItems;
    struct items itm[50];
};
//functions to generate biils
void generateBillHeader(char name[50],char date[30])
	{
    	printf("\n\n");
    	printf("\t\t   *******");
    	printf("\n----------------------------------------------");
        printf("\n\t<<<RESTURANT BILLING SYSTEM>>>");
        printf("\n----------------------------------------------");
        printf("\n\t\t\tDate:%s",date);
        printf("\nInvoice To: %s",name);
        printf("\n");
        printf("-----------------------------------------------\n");
        printf("Items\t\t");
        printf("Qty\t");
        printf("Price\t\t");
        printf("Total\t");
        printf("\n-----------------------------------------------");
        printf("\n\n");
}
void generateBillBody(char item[30],int qty, float price){
    	printf("%s\t\t",item); 
        printf("%d\t",qty);
		printf("%.1f\t\t",price); 
        printf("%.2f\t",qty * price); 
        printf("\n");
}



void generateBillFooter(float total){
    printf("\n");
    float dis = 0.1*total;
    float netTotal=total-dis;
    float tax=0.13*netTotal,grandTotal=netTotal + tax;
    printf("------------------------------------------------\n");
    printf("Gross-Total\t\t\t\t%.2f",total);
    printf("\nDiscount @10%s\t\t\t\t-%.2f","%",dis);
    printf("\n\t\t\t\t\t--------");
    printf("\nNet Total\t\t\t\t%.2f",netTotal);
    printf("\nVAT @ 13%s\t\t\t\t+%.2f","%",tax);
    printf("\n-------------------------------------------------");
    printf("\nGrand Total\t\t\t\t%.2f",grandTotal);
    printf("\n-------------------------------------------------\n");
    printf("\n\t  *** Thanks For Visiting Us ***\n\n");
}
int main()
{


    int opt,n;
    struct orders ord;
    struct orders order;
    char saveBill = 'y',contFlag = 'y';
    char name[50];
    FILE *fp;

    //dashboard
    while(contFlag == 'y')
    {
        system("cls");
        float total = 0;
        int invoiceFound = 0;
        printf("============RESTAURANT BILLING SYSTEM============");
        printf("\n\nPlease select your prefered operation:");
        printf("\n\n1.Generate Invoice");
        printf("\n2.Show all Records");
        printf("\n3.Search Record");
        printf("\n4.Exit");

        printf("\n\nYour choice:\t");
        scanf("%d",&opt);
        fgetc(stdin);

        switch(opt){

            //to create bill
            case 1:
            system("cls");
            printf("============RESTAURANT BILLING SYSTEM============\n");
            //printf("\t\t*****");
            printf("\nName of the customer:\t");
            fgets(ord.customer,50,stdin);
            ord.customer[strlen(ord.customer)-1] = 0;
            strcpy(ord.date,__DATE__);
            // printf("\nPlease enter the number of items:\t");
            printf("\nNo. of items ordered:\t");
            scanf("%d",&n);
            ord.numOfItems = n;
            printf("\t=================================");

            for(int i=0;i<n;i++){
                fgetc(stdin);
                printf("\n\n");
                printf("Enter Name of Item no.%d.:\t",i+1);
                fgets(ord.itm[i].item,20,stdin);
                ord.itm[i].item[strlen(ord.itm[i].item)-1]=0;
                printf("Enter Quantity ordered..:\t");
                scanf("%d",&ord.itm[i].qty);
                printf("Enter Unit price of Item:\t");
                scanf("%f",&ord.itm[i].price);
                total += ord.itm[i].qty * ord.itm[i].price;
                printf("\t\t\t--------------\n");
                printf("\t\t\tTotal:\t%.2f",ord.itm[i].qty * ord.itm[i].price);
                printf("\n\t\t\t--------------");
            }

            system("cls");
            generateBillHeader(ord.customer,ord.date);

            for(int i=0;i<ord.numOfItems;i++){
                generateBillBody(ord.itm[i].item,ord.itm[i].qty,ord.itm[i].price);
            }

            generateBillFooter(total);

            printf("\nDo you want to save the invoice [y/n]:\t");
            scanf("%s",&saveBill);

            if(saveBill == 'y'){
                fp = fopen("RestaurantBill.txt","a+");
                fwrite(&ord,sizeof(struct orders),1,fp);
                if(fwrite != 0)
                printf("\nSuccessfully saved !!!\n");
                else 
                printf("\nError saving");
                fclose(fp);
            }
            break;

            //to show all previous record
            case 2:
            system("cls");
            fp = fopen("RestaurantBill.txt", "r");
            if (fp == NULL)
            {
                printf("No invoices found.\n");
            } 
            else
            {
                printf("============RESTAURANT BILLING SYSTEM============\n");
                printf("\n\t*****Your Previous Records*****\n");
                while (fread(&order, sizeof(struct orders), 1, fp)) {
                    float tot = 0;
                    generateBillHeader(order.customer, order.date);
                    for (int i = 0; i < order.numOfItems; i++)
                    {
                        generateBillBody(order.itm[i].item, order.itm[i].qty, order.itm[i].price);
                        tot += order.itm[i].qty * order.itm[i].price;
                    }
                    generateBillFooter(tot);
                }
                fclose(fp);
            }
            break;

            //to search individual record
            case 3:
            printf("Enter the name of the customer:\t");
            //fgetc(stdin);
            fgets(name,50,stdin);
            name[strlen(name)-1] = 0;
            system("cls");
            fp = fopen("RestaurantBill.txt","r");
            printf("============RESTAURANT BILLING SYSTEM============\n");
            while(fread(&order,sizeof(struct orders), 1, fp))
            {
                float tot = 0;
                if(!strcmp(order.customer,name))
                {
                    printf("\n\t*****Record of %s*****",name);
                    generateBillHeader(order.customer,order.date);
                    for(int i=0;i<order.numOfItems;i++){
                        generateBillBody(order.itm[i].item,order.itm[i].qty,order.itm[i].price);
                        tot+=order.itm[i].qty * order.itm[i].price;
                    }
                    generateBillFooter(tot);
                    invoiceFound = 1;
                }
            }
            if(!invoiceFound){
                printf("\n\nSorry!!! The Record of %s doesnot exists.\n\n",name);
            }
            fclose(fp);
            break;

            case 4:
            printf("\n\t\t Bye Bye :)\n\n");
            exit(0);
            break;

            default:
            printf("Sorry!! Invalid Option");
            break;
        }
        printf("\nDo you want to perform another operation?[y/n]:\t");
        scanf("%s",&contFlag);
    }
    printf("\n\t\t Bye Bye :)\n\n");
    printf("\n\n");

    return 0;
}
