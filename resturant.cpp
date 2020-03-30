#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;
static string usern;
class user { //for the login system
	public:
		string username; 
		string password;
		string inputusername;
		string inputpassword;
		void userregdo() //for making the registration and appending in the user data file
		{
			ofstream usersFile("userdata.txt", ios::app); //appending the file
			if(!usersFile.is_open())
			{
				usersFile.open("userdata.txt");
			}
			usersFile<<username<<" "<<password<<endl; //storing the username and pass in a line
			::usern = username; //storing the username
			usersFile.close();
		}
		void userregister()
		{
			cout<<"Welcome, Please register\nEnter a username"<<endl;  //for processing the registration
			cin>>username;
			cout<<"Please enter a new Password";
			cin>>password;
		}
		void login() //for login
		{
			cout<<"Please enter your username"<<endl;
			cin>>inputusername;
			cout<<"\nPlease enter your password"<<endl;
			cin>>inputpassword;
			string userpass = inputusername+" "+inputpassword; //making the same pattern to match the file content
			bool found = false;
			string line;
			ifstream usersFile;
			usersFile.open("userdata.txt", ios::app);
			if(usersFile.is_open()) //opening the file
			{
				while(getline(usersFile,line) && !found) //checking for contents of file.
				{
					if(line.compare(userpass) == 0) //using the string compare function to get results.
					{
						::usern = inputusername;
						found = true; //if found the loop will stop.
					}
				}
				usersFile.close();
				if(found) //if found the login is successful and will move to next stage.
				{
					cout<<"Login Attempt successful"<<userpass<<endl;
				}
				else {
					cout<<"Login failed, Enter correct details"<<endl;
					login(); //if failed error will be displayed and recursively login function will be called again.
				}
			}	
		}
}u;
class admin {public:
	void adminchoices()
	{
		cout<<"Enter 1 to add menu item"<<endl;
		cout<<"Enter 2 to delete menu item"<<endl;
		cout<<"Enter 3 to change price of a particular item"<<endl;
		cout<<"Enter 4 to exit"<<endl;
		int c;
		cin>>c;
		switch(c)
		{
			case 1:addmenu();
			break;
			case 2:delmenu();
			break;
			case 3:changeprice();
			break;
			case 4:exit(0);
			break;
			default:cout<<"Wrong choice"<<endl;
		}
	}
	void addmenu()
	{
		ofstream menu("menu.txt",ios::app);
		if(!menu)
		{
			menu.open("menu.txt");
		}
		cout<<"Enter dish name to be added"<<endl;
		string dish;
		cin>>dish;
		cout<<"Enter dish price"<<endl;
		string price;
		cin>>price;
		menu<<dish<<" "<<price<<endl;
		cout<<"Enter 1 to add more"<<endl;
		int c;
		cin>>c;
		if(c==1)
			addmenu();
	}
	bool search(string word) //search function for searching the name
		{
			ifstream dealf("menu.txt"); //opening the file in read mode
			if(!dealf) //checking for all types of flags
			{
				dealf.open("menu.txt"); //if file to open this will work
			}
			bool found=false; //default value
			string line; //temp string
			while(dealf >> line && found==false) //condition to read file and checking the name
			{
				if(line.compare(word)==0) //comparing the word with line from file
				{
					found = true; //if found this will break the while loop
				}
			}
			return found; //return search status
		}
	void eraseFileLine(string eraseLine) {
			string line;
			ifstream fin;
			string path = "menu.txt";
			fin.open("menu.txt");
			ofstream temp; // contents of path must be copied to a temp file then renamed back to the path file
			temp.open("temp1.txt");
			
			while (getline(fin, line)) {
			    if (line != eraseLine) // write all lines to temp other than the line marked fro erasing
			        temp << line <<endl;
			}
			
			temp.close();
			fin.close();
			
			const char * p = path.c_str(); // required conversion for remove and rename functions
			remove(p);
			rename("temp1.txt", p);
		}
		void delmenu()
		{
			cout<<"Enter dish name which is to be deleted"<<endl;
			string dish;
			cin>>dish;
			bool found = search(dish);
			if(!found)
			{
				cout<<"Error, no such dish present"<<endl;
			}
			else {
				ifstream dishh("menu.txt");
				if(!dishh)
				{
					dishh.open("menu.txt");
				}
				int count;
				while(!dishh.eof())
				{
					string temp = "";
					getline(dishh,temp); //getting line from file in temp
					count++;
					for(int i=0;i<dish.size();i++)
					{
						if(temp[i]==dish[i])
							found = true; //getting that line which is to be deleted
						else
						{
							found=false;
							break;
						}
					}
					if(found)
					{
						dishh.close(); //closing file forcefully so that it doesnt interferes with remove and rename functions.
						eraseFileLine(temp); //calling erasefile function to delete the temp line which matches with hardware name
						cout<<"Deletion of item...done"<<endl;
					}
					else {
						continue; //else continuing the loop
					}
				}
			}
		}
		void rewrite_line(int n,string rewrite) //function for rewriting a specific line in file
		{ 
		    ifstream filein("menu.txt"); //opening file in read mode
		    ofstream fileout("temp.txt"); //making a temp file in write mode
		    if(!filein || !fileout) //checking for all flags
			{
		        cout << "Error opening files!" << endl;
		    }
		    string strTemp; //temp string
		    int lineno=1; //line counter
		 	while(getline(filein,strTemp)) //reading file
		    {
		    	lineno++; //counting lines
		        if(lineno == n) //if line matches with desired line to change
				{
		            strTemp = rewrite; //then rewriting the data with new data
		        }
		        strTemp += "\n"; //going ahead
		        fileout << strTemp; //writing data 
		    }
		    filein.close(); //closing the files forcefully
		    fileout.close(); //closing the files forcefully
		    remove("menu.txt"); //removing previous file
		    rename("temp.txt","menu.txt"); //replacing with the new file
		} 
		void changeprice()
		{
			string dish,price;
			cout<<"Enter dish name"<<endl; //taking inputs
			cin>>dish;
			cout<<"Enter dish price"<<endl;
			cin>>price;
			string key = dish+" "+price;
			bool check = search(dish); //checking for hardware presence
			if(!check)
			{
				cout<<"No such dish found"<<endl;
			}
			else {
				ifstream dealff("menu.txt"); //opening file
				if(!dealff)
				{
					dealff.open("menu.txt");
				}
				cout<<"Enter new dish price"<<endl; //getting new price
				string pricenew,newkey="";
				cin>>pricenew;
				int count=1; //setting counter for line
				string line="error",temp;
				while(getline(dealff,line)) //getting the line
				{
					count++;
					if(line.compare(key)==0) //comparing with the key
					{
						stringstream s(line); //making a stream to get token after each space
						while(getline(s,temp,' '))
						{
							if(temp.compare(dish)!=0)
							{
								newkey+=pricenew;
							}
							else {
								newkey+=dish+" ";
							}
						}
						dealff.close(); //closing file forcefully
						rewrite_line(count,newkey); //rewriting line 
						cout<<"Prices changed"<<endl;
					}
				}
			}
		}
}a;
class customer {
	public:
		void showmenu()
		{
			ifstream menu("menu.txt");
			if(!menu)
			{
				menu.open("menu.txt");
			}
			string line;
			while(!menu.eof())
			{
				getline(menu,line);
				cout<<line<<endl;
			}
			cout<<"Do you want to order food, if yes press 1"<<endl;
			int c;
			cin>>c;
			if(c==1)
				orderfood();
		}
		void orderfood()
		{
			cout<<"Enter dish name to be ordered"<<endl;
			string dish;
			cin>>dish;
			bool found = a.search(dish);
			if(!found)
			{
				cout<<"no such dish found"<<endl;
				orderfood();
			}
			else {
				ofstream ordered("orderedfood.txt",ios::app);
				if(!ordered)
				{
					ordered.open("orderedfood.txt");
				}
				ifstream dishh("menu.txt");
				if(!dishh)
				{
					dishh.open("menu.txt");
				}
				int count;
				while(!dishh.eof())
				{
					string temp = "";
					getline(dishh,temp); //getting line from file in temp
					count++;
					for(int i=0;i<dish.size();i++)
					{
						if(temp[i]==dish[i])
							found = true; //getting that line which is to be deleted
						else
						{
							found=false;
							break;
						}
					}
					if(found)
					{
						ordered<<temp<<endl;
						cout<<"Enter 1 if you wish to add more item"<<endl;
						int ch;
						cin>>ch;
						if(ch==1)
							orderfood();
						else
							readorder();
							break;
					}
					else {
						continue;
					}
			}
		}
	}
	void readorder()
	{
		ifstream order("orderedfood.txt");
		if(!order)
		{
			order.open("orderedfood.txt");
		}
		string line,temp;
		int finprice=0;
		cout<<"-------------BILL DETAILS--------------"<<endl;
		while(getline(order,line))
		{
			cout<<line<<endl;
			int count=1;
			stringstream s(line); //making a stream to get token after each space
			while(getline(s,temp,' '))
			{
				if(count==2)
				{
					finprice+=stoi(temp);	
				}
				count++;
			}
		}
		cout<<"--------Please do the payment at counter-----------"<<endl;
		cout<<"Total Amount you Have To pay is --"<<finprice<<endl;
		cout<<"Ordered food has been stored in text file.."<<endl;
	}
	void givefeedback()
	{
		cout<<"Enter your name"<<endl;
		string name;
		cin>>name;
		cout<<"Enter favourite dish name"<<endl;
		string dish;
		cin>>dish;
		cout<<"Enter any feedback if you want to or just press space and enter"<<endl;
		string feed;
		cin.ignore();
		getline(cin,feed);
		ofstream feedbacks("feedback.txt",ios::app);
		if(!feedbacks)
		{
			feedbacks.open("feedback.txt");
		}
		feedbacks<<name<<endl;
		feedbacks<<dish<<"  "<<feed<<endl;
	}
	void showfeedback()
	{
		ifstream feedback("feedback.txt");
		if(!feedback)
		{
			feedback.open("feedback.txt");
		}
		string line;
		while(getline(feedback,line))
		{
			cout<<line<<endl;
		}
	}
}cust;
main()
{
	remove("orderedfood.txt");
	cout<<"Welcome to The Online Resturant Bill System... "<<endl;
	cout<<"Enter 1 to Login/Signup as Admin"<<endl;
	cout<<"Enter 2 to show menu"<<endl;
	cout<<"Enter 3 to order food"<<endl;
	cout<<"Enter 4 to read valuable feedback regarding dishes from our customers if its hard making a choice"<<endl;
	cout<<"Enter 5 to give valuable feedback so that other customers get benefitted"<<endl;
	cout<<"Enter 6 to exit"<<endl;
	int c,ch,pass;
	cin>>c;
	switch(c)
	{
		case 1:cout<<"Enter 1 to login as admin"<<endl;
			cout<<"Enter 2 to signup as admin"<<endl;
			cout<<"Enter 3 to exit"<<endl;
			cin>>ch;
			while(pass==0) {
			switch(ch)
			{
				case 1:u.login();
				a.adminchoices();
				pass=1;
				break;
				case 2:u.userregister();
				u.userregdo();
				a.adminchoices();
				pass=1;
				break;
				case 3:pass=1;
				break;
				default:cout<<"Enter correct choice"<<endl;
			}
		}
		break;
		case 2:cust.showmenu();
		break;
		case 3:cust.orderfood();
		break;
		case 4:cust.showfeedback();
		break;
		case 5:cust.givefeedback();
		break;
		case 6:exit(0);
		break;
		default:cout<<"enter correct choice"<<endl;
		break;
	}
}
