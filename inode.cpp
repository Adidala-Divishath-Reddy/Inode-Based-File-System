#include <iostream>
#include <fstream>
#include <bits/stdc++.h>
using namespace std;
long long int disk_size = 524288000, dbsize = 4096, temp;
char buf[4096];
int mode;
string current_open_file="";
struct inode
{
    string file_name;
    long long int file_size;
    long long int file_location;
};
int iarr[5];
vector<pair<long long int, struct inode>> datablocks(((524288000 / 4096)));
unordered_map<string,string> um;
int main()
{
    //fstream file;
    //FILE *fp = (FILE *)file.open("disk.txt",ios::out);
    // FILE *fp = fopen("disk.txt","w");
    // fpos_t position(524288000);
    // fsetpos(fp, &position);
    // cout<<fseek(fp,524288000,SEEK_SET);
    // fstream myFile("disk.txt", ios::in | ios::out | ios::trunc);
    // myFile.seekg(524288000 , ios::beg);
    fstream fs;
    int choice;
    string disk_name = "";
    while (1)
    {
        cout << "Choose one from below\n1.Create Disk\n2.Mount Disk\n3.Exit" << endl;
        cin >> choice;
        switch (choice)
        {
        case 1:
        {
            cout << "Enter new unique Disk name" << endl;
            cin >> disk_name;
            fs.open(disk_name, ios::out);
            fs.seekp(disk_size, ios::beg);
            fs.write("a", 1);
            fs.seekp(0, ios::beg); //pointing to first block(super block)

            // fs.seekp(dbsize, ios::beg); //pointing to second block(inodes block)
            // temp = dbsize;
            // while (temp--)
            //     fs << "0";
            for (int i = 0; i < (524288000 / 4096); i++)
                datablocks[i].first = 0;
            // char ch;
            // fs.seekp(dbsize, ios::beg);
            // fs>>ch;
            // cout<<ch<<endl;
            // temp = dbsize;
            // char c;
            // char buf[4096];
            // strcpy(buf, disk_name.c_str());
            // FILE *fp = fopen(buf,"r");
            // while(temp--){
            //     c = getc(fp);
            //     cout<<c<<endl;
            // }
            // fs.seekp(2*dbsize, ios::beg);//pointing to Third block(data block)
            // fs.seekp(3*dbsize, ios::beg);//pointing to fourth block(inode block)
            // fs.seekp(4*dbsize, ios::beg);//pointing to fifth block(inode block)
            // fs.seekp(5*dbsize, ios::beg);//pointing to sixth block(inode block)

            fs.close();
        }
        break;
        case 2:
        {
            cout << "Enter Disk name to be mounted" << endl;
            // unordered_map<char
            string current_disk = "";
            cin >> current_disk;
            strcpy(buf, current_disk.c_str());
            fstream fs;
            fs.open(buf, ios::in | ios::out);
            fs.seekp(dbsize, ios::beg);
            for (int i = 0; i < 5; i++)
            {
                iarr[i] = (i + 3) * dbsize;
            }
            while (1)
            {
                int flag = 0;
                cout << "1. create file\n2. open file\n3. read file\n4. write file\n5. append file\n6. close file\n7. delete file\n8. list of files\n9. list of opened files\n10.unmount\n";
                int choice;
                cin >> choice;
                switch (choice)
                {
                case 1:
                {
                    cout << "***Enter file name:***\n";
                    string file_name;
                    cin >> file_name;
                    inode in = inode();
                    in.file_name = file_name;
                    in.file_size = 0;
                    long long int i = 0;
                    for (; i < (524288000 / 4096); i++)
                    {
                        if (datablocks[i].first == 0)
                        {
                            cout << "***File created succesfully***\n";
                            datablocks[i].first = 1;
                            in.file_location = i * dbsize;
                            datablocks[i].second = in;
                            // cout<<"created: "<<datablocks[i].second.file_name<<endl;
                            break;
                        }
                    }
                    if (i == (524288000 / 4096))
                        cout << "***Disk is full. No space available***\n";
                    // fs.seekp(i*dbsize, ios::beg);
                    // for (int i = 0; i < file_name.length() - 1; i++)
                    //     fs << file_name[i];

                    // fs << ",";
                    // fs << "file size is";
                    // fs << "0";
                }
                break;
                case 2:
                {
                    string file_name;
                    cout << "Enter file to be opened:\n";
                    cin >> file_name;

                    cout << "Choose mode to be opened:\n1.Read only\n2.Write\n3.append\n";
                    cin >> mode;
                    long long int i = 0;
                    for (; i < (524288000 / 4096); i++)
                    {
                        if (datablocks[i].second.file_name == file_name)
                        {
                            fs.seekp(datablocks[i].second.file_location, ios::beg);
                            cout << "***File Opened Successfully***\n";
                            if(um.find(file_name) == um.end())
                                um[file_name] = file_name;
                            // current_open_file = file_name;
                            // cout << "fs is at location: " << datablocks[i].second.file_location << endl;
                            break;
                        }
                    }
                }
                break;
                case 3:
                {
                    string file_name;
                    cout << "Enter file name to be read:\n";
                    cin >> file_name;
                    long long int i = 0;
                    for (; i < (524288000 / 4096); i++)
                    {
                        if (datablocks[i].second.file_name == file_name)
                        {
                            fs.seekg(datablocks[i].second.file_location);
                            cout << "***File Opened Successfully***\n";
                            // cout << "fs is at location: " << datablocks[i].second.file_location << endl;
                            break;
                        }
                    }
                    char buf[4096];
                    fs.read(buf, 4096);
                    // cout << "Buf is: " << buf << endl;
                    string s = (string)buf;
                    // cout << "S is: " << s << endl;
                    // cout << "Before loop" << endl;
                    for (long long int i = 0; i < s.length(); i++)
                    {
                        if (s[i] == '#')
                        {
                            if (s[i + 1] == '$')
                                break;
                            else
                                cout << endl;
                        }
                        else
                            cout << s[i];
                    }
                    cout<<endl;
                    // char ch;
                    // for (int i = 0; i < 4096; i++)
                    // {
                    // fs >> ch;
                    // if(ch == '-')
                    //     break;
                    // cout << ch;
                    // }
                }

                break;
                case 4:
                {
                    if (mode == 1)
                    {
                        cout << "You opened in read only mode\n";
                        break;
                    }
                    string s = "";
                    long long int i = 0,fl = 0;
                    cout<<endl;
                    for (; i < 4096; i++)
                    {
                        string ch = "";
                        // s += ch;
                        // cin >> ch;
                        getline(cin,ch);
                        if (ch == "end")
                        {
                            s += "#$";
                            break;
                        }
                        if(fl == 0){
                            // cout<<"inside loop\n";
                            s+=ch;
                            fl =1;
                        }
                        else
                            s += "#" + ch;
                    }
                    // cout<<"Before writing: "<<s<<endl;//remove this
                    fs.write(s.c_str(), s.length());
                    // char ch,buffer[4096];

                    // long long int i = 0;
                    // for(;i<4096;i++){
                    //     // string s = "";
                    //     // s += ch;
                    //     cin>>ch;
                    //     if(ch == '-')
                    //         break;
                    //     buffer[i]= ch;

                    // }
                    // fs.write(buffer,i);
                }
                break;
                case 5:
                {
                    long long int temp_loc;
                    if (mode == 1)
                    {
                        cout << "You opened in read only mode\n";
                        break;
                    }
                    string file_name;
                    cout << "Enter file name:\n";
                    cin >> file_name;
                    long long int i = 0;
                    for (; i < (524288000 / 4096); i++)
                    {
                        if (datablocks[i].second.file_name == file_name)
                        {
                            fs.seekg(datablocks[i].second.file_location);
                            temp_loc = datablocks[i].second.file_location;
                            // cout << "***File Opened Successfully***\n";
                            // cout << "fs is at location: " << datablocks[i].second.file_location << endl;
                            break;
                        }
                    }
                    char buf[4096];
                    fs.read(buf, 4096);
                    // cout << "Buf is: " << buf << endl;
                    string s = (string)buf;
                    // cout << "S is: " << s << endl;
                    // cout << "Before loop" << endl;
                    i = 0;
                    for (; i < s.length(); i++)
                    {
                        if (s[i] == '#')
                        {
                            if (s[i + 1] == '$')
                                break;
                        }
                    }
                    s = s.substr(0, i);
                    // cout << "S after modification: " << s << endl;
                    i = 0;
                    int fl = 0;
                    cout<<"Enter the content: "<<endl;
                    for (; i < 4096 - s.length(); i++)
                    {
                        string ch = "";
                        // s += ch;
                        // cin >> ch;
                        getline(cin,ch);
                        if (ch == "end")
                        {
                            s += "#$";
                            break;
                        }
                        if(fl == 0){
                            s+=ch;
                            fl = 1;
                        }
                        else
                        s += "#" + ch;
                    }
                    // cout << "S before inserting: " << s << endl;
                    fs.seekp(temp_loc);
                    // cout << "***File Opened Successfully***\n";
                    // cout << "fs is at location: " << temp_loc << endl;
                    fs.write(s.c_str(), s.length());
                }
                break;
                case 6:
                {
                    cout<<"Enter file name: \n";
                    string file_name;
                    cin>>file_name;
                    if(um.find(file_name) == um.end())
                        cout<<"File is not opened. So cannot close\n";
                    else{
                        um.erase(file_name);
                        cout << "***file closed succesfully***\n";
                    }
                }
                    

                    
                    break;
                case 7:
                {
                    string file_name;
                    cout << "Enter file name:\n";
                    cin >> file_name;
                    long long int i = 0;
                    for (; i < (524288000 / 4096); i++)
                    {
                        if (datablocks[i].second.file_name == file_name)
                        {
                            datablocks[i].first = 0;
                            um.erase(file_name);
                            break;
                        }
                    }
                    if (i == (524288000 / 4096))
                        cout << "***File is not available***\n";
                    else
                        cout<<"File "<<file_name<<" deleted Successfully\n";
                }
                break;
                case 8:
                {

                    long long int i = 0;
                    cout << "***List of files:***" << endl;
                    for (; i < (524288000 / 4096); i++)
                    {
                        if (datablocks[i].first == 1)
                        {
                            inode tempin = inode();
                            tempin = datablocks[i].second;

                            cout << tempin.file_name << endl;
                        }
                    }
                }
                break;
                case 9:{
                    cout<<"List of Opened Files:\n";
                    for(auto it: um)
                        cout<<it.second<<endl;
                }
                    break;
                case 10:
                    flag = 1;
                    cout << "***Unmounted Successfully***\n";
                    fs.close();
                    break;
                }
                if (flag == 1)
                    break;
            }
            // fs.seekp(dbsize, ios::beg);
            // char ch;
            // for (int i = 0; i < 4096; i++)
            // {
            //     fs >> ch;
            //     cout << ch;
            // }
        }
        break;
        case 3:
            return 0;
            break;
        }
    }
    // opening the file in writing mode

    return 0;
}