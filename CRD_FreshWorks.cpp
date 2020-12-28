#include <bits/stdc++.h>
using namespace std;

class DB 
{
	int key;
	char value[20];
	
	public:
		int create();
		int store();
		void read(int);
		void testdel();
		void deleteit(int);
		void showdata();
		int checkFileSize();
};

int DB::create()
{
	cout<<"\n"<<"[:)> Enter the KEY of the value to be created:"<<"\n"<<"\n";
	cin>>key;
	cout<<"\n"<<"[:)> Enter the VALUE of the value to be created:"<<"\n"<<"\n";
	cin>>value;
	cout<<"\n";
}

int DB::store()
{
	if(key == 0 && value == NULL)
	{
		cout<<"[:)> Key Value pair not INITIALIZED"<<"\n"<<"\n";
		return(0);
	}
	else
	{
		ofstream fout;
		fout.open("file.txt",ios::app|ios::binary);
		fout.write((char*)this,sizeof(*this));
		fout.close();
		cout<<"{} DATA written to FILE {}"<<"\n"<<"\n";
		return(1);
	}
}

void DB::read(int keyx)
{	
	int flag2 = 0;
    int pos;
    ifstream ifs;
    ifs.open("file.txt", ios::in | ios::binary);
  
    while (!ifs.eof()) 
	{
        ifs.read((char*)this, sizeof(DB));
        if (ifs) 
		{
            if (keyx == key) 
			{
                cout <<"\n"<<"[:)> RECORD FOUND the DATA is"<<"\n"<<"\n";
                showdata();
            }
            else
            {
            	cout<< "[:)> RECORD not FOUND"<<"\n"<<"\n";
			}
        }
    }
    ifs.close();
}

void DB::testdel()
{
	cout<<"[:)> Enter the key to be deleted"<<"\n"<<"\n";
    int keyy;
    cin>>keyy;
    cout<<"\n"<<"\n";
	deleteit(keyy);
} 

void DB::deleteit(int k)
{
	int pos, flag = 0;
	ifstream ifs;
	ifs.open("file.txt", ios::in | ios::binary);
	ofstream ofs;
	ofs.open("temp.txt", ios::out | ios::binary);

	while (!ifs.eof())
	{
		ifs.read((char*)this, sizeof(DB)); 

		if (ifs) 
		{
			if (k == key) 
			{
				flag = 1;
				cout << "[:)> The deleted record is"<<"\n"<<"\n";
				showdata();
			}
			else 
			{
				ofs.write((char*)this, sizeof(DB));
			}
		}
	}
	
	ofs.close();
	ifs.close();
	remove("file.txt");
	rename("temp.txt", "file.txt");
	if (flag == 1)
		cout <<"[:)> Record successfully deleted"<<"\n"<<"\n";
	else
		cout <<"[:)> Record not found"<<"\n"<<"\n";
} 

void DB::showdata()
{ 
	cout <<"KEY:";
	cout << key<<"\n";
	cout <<"VALUE:";
	cout << value<<"\n"<<"\n";
}

int DB::checkFileSize() 
{
	int flag = 0;
   	ifstream in_file("file.txt", ios::binary);
   	in_file.seekg(0, ios::end);
   	int file_size = in_file.tellg();
   	for(int i=0;i<3;i++)
   	{
   		int num = 1024;
   		file_size = file_size/num;
	}
   	if (file_size < 1)
   	{
   		flag = 0;
   	}
   	return flag;
}

int main()
{
	char choise = 'c';
	while (choise == 'c')
	{
		DB v;
		int flag = v.checkFileSize();
		char ch;
		cout<<"[:)>  What do you want to do? [ENTER on of the charactrers to execute (c/r/d)]"<<"\n"<<"\n";
		cout<<"[:)> [1.][CREATE][2.][READ][3.][DELETE]"<<"\n"<<"\n";
		cin>>ch;
		
	 	switch (ch) {
        case 'c':
        	if (flag == 1)
        	{
        		cout<<"[:)> The FILE size is 1GB, no more data can be stored"<<"\n"<<"\n";
        		break;
			}
			else
			{
				v.create();
				v.store();
				break;
			}
            break;
        case 'r':
            cout<<"\n"<<"[:)> Enter the key to be searched"<<"\n"<<"\n";
            int keyx;
            cin>>keyx;
            cout<<"\n";
            v.read(keyx);
            break;
        case 'd':
        	cout<<"\n";
            v.testdel();
            break;
        default:
            cout <<"[:)> Error! The input character is not correct"<<"\n"<<"\n";
            break;
    }
    cout<<"[:)> Do you want to continue? [Enter [c] to continue or [e] to exit]"<<"\n";
    cin>>choise;
    cout<<"\n"<<"\n"<<"\n";
	}	
	return 0;
} 
