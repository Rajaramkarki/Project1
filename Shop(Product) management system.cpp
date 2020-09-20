#include<iostream>
#include<fstream>
#include<conio.h>
#include<stdio.h>
#include<string.h>
#include<iomanip>
using namespace std;

class Product
{
      int Price;
      char ProductName[30];
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
};


void Product::accept()
{

        cout<<"Product Name: ";
        fflush(stdin);
		gets(ProductName);
		cout<<"Product Code: ";
		cin>>ProductCode;
		cout<<"Price: ";
        cin>>Price;
        cout<<"Total Quantity: ";
		cin>>totalQ;
		cout<<"Weight(IN K.g.): ";
		cin>>Weight;

}


void Create_bill()
{
    Product p1;
    int i,billno,dd,mm,yyyy;
    char CustomerName[30];
    char phone[10];
    char address[30];
    int ProCode, quantity;
	float totalPrice;
	char found='n';

    cout<<"Bill no:";
    cin>>billno;
    cout<<"Date (dd mm yyyy):";
    cin>>dd>>mm>>yyyy;
    cout<<"Name of customer:";
    fflush(stdin);
    gets(CustomerName);
    cout<<"Address of the customer:";
    fflush(stdin);
    gets(address);
    cout<<"Phone number of the customer:";
    cin>>phone;

    ifstream file("sales.dat",ios::in|ios::binary);
    cout<<"\nEnter the Product Code of the item bought: ";
    cin>>ProCode;
    file.seekg(0,ios::beg);
    while(1)
    {
            file.read((char*)&p1,sizeof(p1));
            if(!file)
               break;
            if(ProCode == p1.getProductCode())
            {
                  cout<<"The Name of the item is "<<p1.getProductName()<<endl;
                  cout<<"The price per unit of the item is "<<p1.getPrice()<<endl;

                  found='y';
            }
    }
    if(found=='n')
       {cout<<"\nPLease check the product code again !!!\n";}
    file.close();
    system("PAUSE");

    cout<<"\nEnter the quantity of the item bought: ";
    cin>>quantity;
    totalPrice = p1.getPrice() * quantity;
    cout<<"The Total amount is "<<totalPrice<<endl;

    cout<<"The bill is:"<<endl;
    cout<<"\n"<<endl;
    cout<<"**************************Pavitra Construction Pvt Ltd.**************************"<<endl;
    cout<<"************************************VAT BILL************************************\n"<<endl;

     cout << setfill(' ')
     << setw(1)  << "PAN No. = 030080100"
     << setw(42) << "Date(DD/MM/YYYY) = "<<dd<<"/"<<mm<<"/"<< yyyy
     << endl;
     cout << setfill(' ')
     << setw(1)  << "Bill no ="<<billno
     << setw(44) << "Customer Name ="<<CustomerName
     << endl;
     cout << setfill(' ')
     << setw(1)  << "Customer Phone ="<<phone
     << setw(35) << "Customer address = "<<address
     << endl;
    cout<<"\n"<<endl;
    cout << setfill(' ')
     << setw(1) << "S.N"
     << setw(20) << "Product Name"
     << setw(20) << "Price Per unit"
     << setw(20) << "Quantity"
     << setw(20) << "Total Amount"
     << endl;
      cout << setfill(' ')
     << setw(1) << "1"
     << setw(18) << p1.getProductName()
     << setw(20) << p1.getPrice()
     << setw(20) << quantity
     << setw(20) << totalPrice
     << endl;
     cout<<"\n"<< endl;
     cout << setfill(' ')
     << setw(81) << "Signature"
     <<endl;
     cout << setfill(' ')
     << setw(81) << "-----------"
     <<endl;

    system("PAUSE");
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
    int NewtotalQ,ProductCodeNew;
    cout<<"\nEnter the new Details...";
    cout<<"\nNew Product Name (Enter '1' to retain old one): ";
    fflush(stdin);   gets(ProductNewName);
    cout<<"\nNew Product Code (Enter '1' to retain old one): ";
    cin>>ProductCodeNew;
	cout<<"\nNew New Total Quantity (Enter 1 to retain old one, ex: 25000): ";
    cin>>NewtotalQ;
    cout<<"\nNew New Weight (Enter 1 to retain old one, ex: 25000): ";
    cin>>WeightNew;
	if(strcmp(ProductNewName,"1")!=0)
	   strcpy(ProductName,ProductNewName);
	if(ProductCodeNew!=1)
	   ProductCode=ProductCodeNew;
	if(NewtotalQ!=1)
	   totalQ=NewtotalQ;
	if(WeightNew!=1)
	   Weight=WeightNew;
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
             cerr<<"\nFile Open Error !!!";
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
		 	cout<<"\nProduct details for Product Code"<<snew.getProductCode()<<" ALREADY EXISTS\n\n";
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
     long pos;
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

void Crete_bill()
{

}

void main_menu()
{

    int choice;
    system("CLS");
    cout<<"*******************************************************************************";
    cout<<"\n\t            \tShop (Sales) Management System\t\t      \n";
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
