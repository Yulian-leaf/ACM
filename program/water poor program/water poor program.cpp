//write and read test in 0.0.8 version
//this test wants to change every things get in ture way
//reduce the text
#include<iostream>
#include<stdio.h>
#include<windows.h>
#include<string.h>

using namespace std;

FILE *test;

void slove()
{
    exit(0);
}

char UserDataName[50];
char UserDataKey[50];
inline int UserDataReader()         //cout the data in list
{
    int onerg = 0;  
    char ch = ' ';
    while(true)
    {
        ch = fgetc(test);
        if(ch == '\n')
        {
            UserDataName[onerg] = ch;
            break;
        }
        else
            UserDataName[onerg++] = ch;
    }
    ch = ' ';   //free the ch in \n and onerg in everyone
    onerg = 0;
    while(true)
    {
        ch = fgetc(test);
        if (ch == '\n')
        {
            UserDataKey[onerg] = ch;
            break;
        }
        else 
            UserDataKey[onerg++] = ch;
    }
    return 0;
}

inline int Checker(char checkone[],char checktwo[])     //check two list similar or not
{
    for(int onerg = 0;onerg <= 50;onerg++)
    {
        if(checkone[onerg] == '\n')
            return 0;
        else if(checkone[onerg] != checktwo[onerg])
            return 1;
    }
    return 1;
}
/*
inline int FreeList(char list[])            //free the list , just for char_list in 50
{
    for(int onerg = 0;onerg <= 50;onerg++)
        list[onerg] = ' ';
    return 0;
}
*/

char Equipment[50][50];
int Equipmentdata[50];
int Equipmentnum = 0;
inline int EquipmentReader()		//for equipment state read
{
	char ch;
	int onergH = 0;
	int onergL = 0;
	int equipmentstate;
	bool chOrint = 0;
	while(true)
	{
		ch = fgetc(test);
		if(ch == '@')
			break;
		else if(!chOrint)			//no chOrint means should input char now 
		{
			if(ch == '\n')
			{
				Equipment[onergL++][onergH] = ch;
				onergH = 0;
			}
			else
				Equipment[onergL][onergH++] = ch;
		}
		else
		{
			if(ch == '\n')	
				chOrint  = 0;
			else
				Equipmentdata[onergL-1] = ch - '0';
		 } 
	}
	Equipmentnum = onergL-1;
	return 0;
}

signed main()
{
    //prepare the test in userdata
    test = fopen("data\\userdata.txt","r");
    UserDataReader();
    fclose(test);
    while(true)
    {
        system("cls");
        //welcome the user and check the user
        cout<<"water poor program"<<endl;
        cout<<endl;
        cout<<"Welcome to the water poor program"<<endl;
        cout<<"if you want to use the program , please login first"<<endl;
        //check the name
        cout<<"yours name(less than 50 long):";
        char UserName[50];
        cin>>UserName;
        bool YesNot;
        YesNot = Checker(UserDataName,UserName);
        if(YesNot)
        {
            system("cls");
            cout<<"yours name get something wrong"<<endl;
            cout<<"please enter anythings and try again"<<endl;
            string nothing;
            cin>>nothing;
//            FreeList(UserName);
            continue;
        }
        //check the key
        cout<<"yours key(less than 50 long):";
        char UserKey[50];
        cin>>UserKey;
        YesNot = Checker(UserDataKey,UserKey);
        if(YesNot)
        {
            system("cls");
            cout<<"yours key get something wrong"<<endl;
            cout<<"please enter anythings and try again"<<endl;
            string nothing;
            cin>>nothing;
//            FreeList(UserName);
//            FreeList(UserKey);
            continue;
        }
        //ture in name and key , welcome the user and tell something
        while(true)
        {
            system("cls");
            cout<<"water poor program"<<endl
            <<endl
            <<"in this program , we have more choice to do"<<endl
            <<"please enter the number to launch the choice"<<endl
            <<endl
            <<"0. quit the program"<<endl
            <<"1. equipment managment"<<endl;
            
            int InputMain;cin>>InputMain;
            //0 , for quit the program
            if(InputMain == 0)
            {
            	system("cls");
            	cout<<"thanks for use the water poor program"<<endl
            	<<"please enter anything to exit"<<endl;
            	string nothing;cin>>nothing;
            	return 0;
			}
			//1 , for check the equipment managment
			else if(InputMain == 1)
			{
				test = fopen("data\\equipmentstate.txt","r");
            	EquipmentReader();
            	fclose(test);
            	
            	system("cls");
            	cout<<"water poor program"<<endl
            	<<"equipment managment"<<endl
            	<<endl
            	<<"please enter the number to choice"<<endl
            	<<"0. back to main"<<endl
            	<<"1. get equipment state"<<endl
            	<<"2. change the equipment state"<<endl;
            	int InputSwitch1;cin>>InputSwitch1;
            	//0 , for back to main
            	//1 , for get equipment state
            	if(InputSwitch1 == 1)
            	{
            		for(int onergH = 0,onergL = 0;onergL <= Equipmentnum;)
            			{
            				cout<<Equipment[onergH++][onergL];
            				if(onergH == 50)
            				{
            					cout<<endl;
            					if(Equipmentdata[onergL] == 1)
            						cout<<"open"<<endl;
            					else
            						cout<<"close"<<endl;
            					onergH = 0;
            					onergL++;
							}
						}
					cout<<"please enter anythings to back main"<<endl;
					string nothing;cin>>nothing;
				}
				else if(InputSwitch1 == 2)
				{
					system("cls");
            		cout<<"1. ";
            		for(int onergH = 0,onergL = 0;onergL <= Equipmentnum;)
            		{
            			cout<<Equipment[onergH++][onergL];
            			if(onergH == 50)
            			{
            				cout<<endl;
            				if(Equipmentdata[onergL] == 1)
            					cout<<"open";
            				else
            					cout<<"close";
            				cout<<endl<<onergL+2<<". ";
            				onergH = 0;
            				onergL++;
						}
					}
					cout<<"which would you want to change ,please enter the number"<<endl;
					int InputSwitch2;cin>>InputSwitch2;
					if(Equipmentdata[InputSwitch2-1] == 1)
						Equipmentdata[InputSwitch2-1] = 0;
					else
						 Equipmentdata[InputSwitch2-1] = 1;
					cout<<"secess to change , please enter anything to back"<<endl;
					string nothing;
					cin>>nothing;
				}
			}
            /*
            switch(InputMain)
            {
            	//0 , for quit the program
            	case 0:
            		system("cls");
            		cout<<"thanks for use the water poor program"<<endl
            		<<"please enter anything to exit"<<endl;
            		string nothing;cin>>nothing;
            		return 0;
            		break;
            	//1 , for check the equipment managment
            	case 1:
            		//prepare for equipment state
            		test = fopen("data\\equipmentstate.txt");
            		EquipmentReader();
            		fclose(test);
            		
            		system("cls");
            		cout<<"water poor program"<<endl
            		<<"equipment managment"<<endl
            		<<endl
            		<<"please enter the number to choice"<<endl
            		<<"0. back to main"<<endl
            		<<"1. get equipment state";
            		<<"2. change the equipment state"
            		int InputSwitch1;cin>>InputSwitch1;
            		switch(InputSwitch1)
            		{
            			//0 , for back to main
            			case 0:
            				break;
            			//1 , for get equipment state
            			case 1:
            				for(int onergH = 0,onergL = 0;onergL <= Equipmentnum;)
            				{
            					cout<<Equipment[onergH++][onergL];
            					if(onergH == 50)
            					{
            						cout<<endl;
            						if(Equipmentdata[onergL] == 1)
            							cout<<"open";
            						else
            							cout<<"close";
            						onergH = 0;
            						onergL++;
								}
							}
							break;
            			case 2:
            				system("cls");
            				cout<<"1. ";
            				for(int onergH = 0,onergL = 0;onergL <= Equipmentnum;)
            				{
            					cout<<Equipment[onergH++][onergL];
            					if(onergH == 50)
            					{
            						cout<<endl;
            						if(Equipmentdata[onergL] == 1)
            							cout<<"open";
            						else
            							cout<<"close";
            						cout<<endl<<onergL+2<<". ";
            						onergH = 0;
            						onergL++;
								}
							}
							cout<<"which would you want to change ,please enter the number"<<endl;
							int InputSwitch2;cin>>InputSwitch2;
							if(Equipmentdata[InputSwitch-1] == 1)
								Equipmentdata[InputSwitch-1] = 0;
							else
								 Equipmentdata[InputSwitch-1] = 1;
							cout<<"secess to change , please enter anything to back"<<endl;
							string nothing;
							cin>>nothing;
							break;
					}
					break;
            		
            		
			}*/
        }
    }
}
