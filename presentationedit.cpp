#include<iostream>
#include<fstream>
#include<conio.h>
#include<string.h>
#include<iomanip>
#include<stdio.h>

using namespace std;

class Product
{
    private:
      int Price;
      char ProductName[40];
      int ProductCode;
      int totalQ;
      float Weight;
    public:
      void accept();
      void show();
      void update();

      int getProductCode()
      {
          return ProductCode;
      }
      int getPrice()
      {
          return Price;
      }
      string getProductName()
      {
          return ProductName;
      }
      int gettotalQ()
      {
          return totalQ;
      }
};

class Bill{
    private:
        int billno,dd,mm,yyyy;

    public:
        void accept();
        int getdd()
        {
            return dd;
        }
        int getmm()
        {
            return mm;
        }
        int getyyyy()
        {
            return yyyy;
        }
        int getbillno()
        {
            return billno;
        }
};


class Customer{
    private:
        char CustomerName[20];
        char phone[10];
    public:
        void accept();
        string getCustomerName()
        {
            return CustomerName;
        }
        string getphone()
        {
            return phone;
        }

};

void Product::accept()
{
    cout<<"Product Name: ";
    fflush(stdin);
    gets(ProductName);
    cout<<"Product Code: ";
    cin>>ProductCode;
    cout<<"Price per unit: ";
    cin>>Price;
    cout<<"Total Quantity: ";
    cin>>totalQ;
    cout<<"Weight(IN K.g. per unit): ";
    cin>>Weight;
}

void Product::show()
{
    cout<<"Product Name: ";
    puts(ProductName);
    cout<<"Product Code: ";
    cout<<ProductCode<<endl;
    cout<<"Price: ";
    cout<<Price<<endl;
    cout<<"Total Quantity: ";
    cout<<totalQ<<endl;
    cout<<"Weight(in K.g) ";
    cout<<Weight<<endl<<endl;
    system("PAUSE");
}

void Product::update()
{
	char ProductNewName[30] ;
    float WeightNew;
    int NewtotalQ,ProductCodeNew,PriceNew;
    cout<<"\nEnter the new Details...";
    cout<<"\nNew Product Name (Enter '1' to retain old one): ";
    fflush(stdin);   gets(ProductNewName);
    cout<<"\nNew Product Code (Enter '1' to retain old one): ";
    cin>>ProductCodeNew;
    cout<<"\nNew Price (Enter '1' to retain old one): ";
    cin>>PriceNew;
	cout<<"\nNew New Total Quantity (Enter 1 to retain old one, ex: 25000): ";
    cin>>NewtotalQ;
    cout<<"\nNew New Weight (Enter 1 to retain old one, ex: 25000): ";
    cin>>WeightNew;
	if(strcmp(ProductNewName,"1")!=0)
	   strcpy(ProductName,ProductNewName);
	if(ProductCodeNew!=1)
	   ProductCode=ProductCodeNew;
    if(PriceNew!=1)
	   Price=PriceNew;
	if(NewtotalQ!=1)
	   totalQ=NewtotalQ;
	if(WeightNew!=1)
	   Weight=WeightNew;
}

void Customer::accept()
{
    cout<<"Name of the customer: ";
    fflush(stdin);
    gets(CustomerName);
    cout<<"Phone number of customer: ";
    cin>>phone;
}

void Bill::accept()
{
    cout<<"Date (mm dd yyyy):";
    cin>>mm>>dd>>yyyy;
    cout<<"Bill no:";
    cin>>billno;
}

void Search_Product()
{
    Product p1;
	int ProCode;
	char found='n';
    ifstream file("sales.dat",ios::in|ios::binary);
    cout<<"\nEnter the Product Code to search: ";
    cin>>ProCode;
    file.seekg(0,ios::beg);
    while(1)
    {
            file.read((char*)&p1,sizeof(p1));
            if(!file)
               break;
            if(ProCode == p1.getProductCode())
            {
                  p1.show();
                  found='y';
            }
    }
    if(found=='n')
       cout<<"\nNO RECORD FOUND !!!\n";
    file.close();
    system("PAUSE");
}

void Read_Records()
{
    Product p1;
      ifstream f1("sales.dat",ios::in|ios::binary);
      if(!f1)
      {
             cout<<"\nFile Open Error !!!";
             return;
      }
      while(f1.read((char*)&p1,sizeof(p1)))
      {
              p1.show();
      }
      f1.close();
}

void Insert_record()
{
    Product p1;

     ifstream fi("sales.dat",ios::in|ios::binary);
     ofstream fo("temp.dat",ios::out|ios::binary);
     char last='y', duplicate='n';
     Product snew;
	 cout<<"\nEnter the details of the new Record: \n";
	 snew.accept();
	 while(fi.read((char*)&p1,sizeof(p1)))
	 {
         if(snew.getProductCode()==p1.getProductCode())
		 {
		 	cout<<"\nProduct details for Product Code "<<snew.getProductCode()<<" ALREADY EXISTS\n\n";
		 	duplicate='y';
			goto label;
		 }
         if(snew.getProductCode()<=p1.getProductCode())
         {
             fo.write((char*)&snew,sizeof(snew));
             last='n';
             break;
         }
         else
         	 fo.write((char*)&p1,sizeof(p1));
     }
     if(last=='y')
         fo.write((char*)&snew,sizeof(snew));
     else if(!fi.eof())
     {
        while(1)
        {
           if(!fi)
              break;
           fi.read((char*)&p1,sizeof(p1));
           fo.write((char*)&p1,sizeof(p1));
           if(!fi)
              break;
        }
     }
     fi.close();
     fo.close();
     remove("sales.dat");
     rename("temp.dat","sales.dat");
     cout<<"\nProduct Added Successfully !!!\n";
     label:
     if(duplicate=='y')
     {
     	remove("temp.dat");
	 }
	 system("PAUSE");
}

void Delete_record()
{
    Product p1;
     ifstream fi("sales.dat",ios::in|ios::binary);
     ofstream fo("temp.dat",ios::out|ios::binary);
     int pID=0;
     char found='f';
     cout<<"\nEnter the Product Code to be deleted: ";
	 cin>>pID;
     while(fi.read((char*)&p1,sizeof(p1)))
     {
              if(pID==p1.getProductCode())
              {
                   cout<<"\nDetails of the Product to be deleted\n";
                   p1.show();
                   found='t';
                   continue;
              }
              else
                   fo.write((char*)&p1,sizeof(p1));

      }
      if(found=='f')
        cout<<"\n\n\t\tRECORD NOT FOUND !!!\n\n";
      else
        cout<<"\n\n\t\tRecord Deleted Successfully !!!\n\n";
      fi.close();
      fo.close();
      remove("sales.dat");
      rename("temp.dat","sales.dat");
      system("PAUSE");
}

void Update_record()
{
    Product p1;
     fstream f1("sales.dat",ios::in|ios::out|ios::binary);
     int pID;
     char found='f';
     cout<<"\nEnter the Product Code to be Updated: ";
	 cin>>pID;
	 if(!f1)
	 {
		cout<<"File not Found";
		exit(0);
	 }
	 else
	 {
		f1.read((char*)&p1, sizeof(p1));
		while(!f1.eof())
		{
			if(pID==p1.getProductCode())
			{
				f1.seekg(0,ios::cur);
				p1.update();
				f1.seekp(f1.tellg() - sizeof(p1));
				f1.write((char*)&p1, sizeof(p1));
				found='t';
				cout<<"\n\n\t\tRECORD UPDATED !!!\n\n";
			}
			f1.read((char*)&p1, sizeof(p1));
		}
	 }

     if(found=='f')
        cout<<"\n\n\t\tRECORD NOT FOUND !!!\n\n";
     f1.close();
     system("PAUSE");
}

void Create_bill()
{
    Product p[10];
    Bill b;
    Customer c;

    int n,i, ProCode[10];
    char found='n';
    int quantity[10];
    float tempprice[10],totalPrice[10],grandTotal = 0;
    string tempname[10];

    cout<<"Please give information about the products: "<<endl;
    cout<<"How many products are bought (max 10 per bill) :";
    cin>>n;
    try
    {
        if(n<0)
            throw n;
    }
    catch(int ex)
    {
        cout<<"Please enter a positive number and restart:"<<endl;
    }
    for(i=0;i<n;i++)
    {

        ifstream file("sales.dat",ios::in|ios::binary);
        cout<<"\nEnter the Product Code of the item "<<i+1<<" :" ;
        cin>>ProCode[i];
        file.seekg(0,ios::beg);
        while(1)
        {
                file.read((char*)&p[i],sizeof(p[i]));
                if(!file)
               break;
                if(ProCode[i] == p[i].getProductCode())
                {
                    cout<<"Name = "<<p[i].getProductName()<<" and price per unit = "<<p[i].getPrice()<< endl;
                    cout<<"Enter the quantity of the item bought (total quantity = "<<p[i].gettotalQ()<<") = ";
                    cin>>quantity[i];
                    try
                    {
                        if(quantity[i]<0)
                            throw quantity[i];


                    }
                    catch(int ex)
                    {
                        quantity[i] = -quantity[i];
                    }
                    found='y';
                    totalPrice[i] = p[i].getPrice() * quantity[i];
                    cout<<"The Total amount is "<<totalPrice[i]<<endl;
                    grandTotal += totalPrice[i];

                    tempprice[i] = p[i].getPrice();
                    tempname[i] = p[i].getProductName();
                }
        }
    if(found=='n')
       {cout<<"\nPLease check the product code again !!!\n";}
    file.close();
    cin.get();
    }

    cout<<"\nPlease enter following information : "<<endl;
    c.accept();
    b.accept();

    cout<<"The bill is:"<<endl;
    cout<<"\n"<<endl;
    cout<<"**************************Pavitra Construction Pvt Ltd.**************************"<<endl;
    cout<<"************************************VAT BILL************************************\n"<<endl;

     cout << setfill(' ')
     << setw(1)  << "PAN No. = 030080100"
     << setw(47) << "Date(DD/MM/YYYY) = " <<b.getmm()<<"/"<<b.getdd()<<"/"<< b.getyyyy()
     << endl;
     cout << setfill(' ')
     << setw(1)  << "Bill no ="<<b.getbillno()
     << setw(50) << "Customer Name = " <<c.getCustomerName()
     << endl;
     cout << setfill(' ')
     << setw(1)  << "Customer Phone = " <<c.getphone()
     << endl;
    cout<<"\n"<<endl;
    cout << setfill(' ')
     << setw(1) << "S.N"
     << setw(20) << "Product Name"
     << setw(20) << "Price Per unit"
     << setw(20) << "Quantity"
     << setw(20) << "Total Amount"
     << endl;

     for(i=0;i<n;++i)
     {
                    cout << setfill(' ')
                    << setw(1) << i+1
                    << setw(18) << tempname[i]
                    << setw(20) << tempprice[i]
                    << setw(20) << quantity[i]
                    << setw(20) << totalPrice[i]
                    << endl;
     }
     cout << "\n"<<endl;
     cout << setfill(' ')
     <<setw(74)<<"Grand Total = "<<grandTotal
     <<endl;

     cout<<"\n"<< endl;
     cout << setfill(' ')
     << setw(81) << "Signature"
     <<endl;
     cout << setfill(' ')
     << setw(82) << "-----------"
     <<endl;

    system("PAUSE");
}

void main_menu()
{

    int choice;
    system("CLS");
    cout<<"*********************************************************************************"<<endl;
    cout<<"**************************Pavitra Construction Pvt Ltd.**************************"<<endl;
    cout<<"\n\t              \t Shop (Sales) Management System\t\t      \n";
    cout<<"*******************************************************************************";
    cout<<"\n\n\t\t\t    <<<<<:: MENU ::>>>>>\n";
    cout<<"\n\t\t\t    1. Add product";
    cout<<"\n\t\t\t    2. Delete Product";
    cout<<"\n\t\t\t    3. Update Product";
    cout<<"\n\t\t\t    4. Display All Products";
    cout<<"\n\t\t\t    5. Search Product (Based on Product Code)";
    cout<<"\n\t\t\t    6. Create Bill";
    cout<<"\n\t\t\t    7. Exit";
    cout<<"\n\t\t\t    Enter your choice: ";
    cin>>choice;
    switch(choice)
    {
           case 1: Insert_record();
                   break;

           case 2: Delete_record();
                   break;

           case 3: Update_record();
                   break;

           case 4: Read_Records();
                   break;

           case 5: Search_Product();
                   break;

           case 6: Create_bill();
                   break;

           case 7: break;

           default: cout<<"\nNo such option...\n\n";
                    system("PAUSE");
                    main_menu();
					break;
    }
    if(choice!=7)
       main_menu();
}

int main()
{
    main_menu();
    getch();
    return 0;
}







