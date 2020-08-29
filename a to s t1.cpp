#include<iostream>
#include<fstream>
#include<conio.h>
#include<stdio.h>
#include<string.h>
using namespace std;

class Product
{
      int Price;
      char ProductName[30];
      char ProductCode[30];
      int totalQ;
      float Weight;
    public:
      void accept();
      void show();
      void update();

      char getProductCode()
      {
          return ProductCode[30];
      }
};

void Product::accept()
{
    Product p1;
        cout<<"\nPrice: ";
        cin>>Price;
        cout<<"Product Name: ";
        fflush(stdin);
		gets(ProductName);
        cout<<"Total Quantity: ";
		cin>>totalQ;
		cout<<"Product Code: ";
		fflush(stdin);
		gets(ProductCode);
		cout<<"Weight(IN K.g.): ";
		cin>>Weight;
}

void Product::show()
{
    Product p1;

        cout<<endl<<"Price: ";
        cout<<Price<<endl;
        cout<<"Product Name: ";
        puts(ProductName);
        cout<<"Total Quantity: ";
		cout<<totalQ<<endl;
		cout<<"Product Code: ";
		puts(ProductCode);
		cout<<"Weight(in K.g) ";
		cout<<Weight<<endl<<endl;
		system("PAUSE");

}

void Product::update()
{
    Product p1;
	char ProductNewName[30], ProductCodeNew[30];
    float WeightNew;
    int NewtotalQ;
    cout<<"\nEnter the new Details...";
    cout<<"\nNew Product Name (Enter '1' to retain old one): ";
    fflush(stdin);   gets(ProductNewName);
    cout<<"\nNew Product Code (Enter '1' to retain old one): ";
    fflush(stdin);   gets(ProductCodeNew);
	cout<<"\nNew New Total Quantity (Enter 1 to retain old one, ex: 25000): ";
    cin>>NewtotalQ;
    cout<<"\nNew New Weight (Enter 1 to retain old one, ex: 25000): ";
    cin>>WeightNew;
	if(strcmp(ProductNewName,"1")!=0)
	   strcpy(ProductName,ProductNewName);
	if(strcmp(ProductCodeNew,"1")!=0)
	   strcpy(ProductCode,ProductCodeNew);
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

