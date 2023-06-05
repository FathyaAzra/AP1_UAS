#include<iostream>
#include<vector>

using namespace std;

struct Task
{
    string Desc;
    bool Completeness;
};

void addTask(vector<Task>& tasks)
{
    system("CLS"); //untuk windows, untuk clear screen
    Task newTask; //variable dengan structure dari Task yg sudah ada
    string desc; //isi dari task (deskripsi)

    cout<<"Enter Task Description : ";
    cin.ignore();
    getline(cin, desc); 

    newTask.Desc = desc;
    newTask.Completeness = false; //task baru otomatis statusnya On-Going

    tasks.push_back(newTask); //menaruh di urutan terakhir

    cout<<"Task successfully added\n\n";
    cout<<"===============================\n\n";
}


void viewTaskfull(vector<Task>& tasks)
{
    system("CLS");
    
    cout<<"To-Do List : \n";
//menampilkan list secara berurut
    for (int i = 0; i<tasks.size(); ++i)
    {
        const Task& task = tasks[i];
        cout<< i + 1<<". " <<(task.Completeness? "[Complete]" : "[On-Going]"); //menampilkan status
        cout<<task.Desc<<'\n';
    }
    cout<<"===============================\n\n";
}

void viewTaskgoing(vector<Task>& tasks)
{
    system("CLS");

    cout<<"To-Do List (On-Going) : \n";
//menampilkan list on going secara berurut (tidak memakai angka karena sudah di filter)
    for (int i = 0; i<tasks.size(); ++i)
    {
        const Task& task = tasks[i];
        if (task.Completeness == false)
        {
            cout<< "- " <<task.Desc<<'\n';
        }
    }
    cout<<"===============================\n\n";
} 
        

void delTask(vector<Task>& tasks)
{
    system("CLS");
    int taskNum; //untuk input list mana yang mau dihapus
    if (tasks.empty()) return; //jika kosong/tidak ada yg bisa dihapus, langsung skip delTask

    do
    {
        taskNum = 0;
        system("CLS");
        viewTaskfull(tasks);
        cout<<"Enter the task number to delete : ";

        while (!(cin >> taskNum) || taskNum <= 0 || taskNum > tasks.size())
        {
            cout << "Invalid input. Please enter a valid task number: ";
            cin.clear();
            cin.ignore();
        } //to filter only integer and in range of to do list
        
    }
    while (taskNum  <= 0 || taskNum > tasks.size());

    tasks.erase(tasks.begin() + taskNum - 1); //penghapusan task
    cout<<"Task deleted successfully!\n\n";
    cout<<"===============================\n\n";
    
}

void markTask(vector<Task>& tasks)
{
    system("CLS");
    int taskNum;
    if (tasks.empty()) return;

    do
    {
        system("CLS");
        viewTaskfull(tasks);
        cout << "Enter the task number to Mark As Done: ";

        taskNum = 0;
        while (!(cin >> taskNum) || taskNum <= 0 || taskNum > tasks.size())
        {
            cout << "Invalid input. Please enter a valid task number: ";
            cin.clear();
            cin.ignore();
        } //to filter only integer and in range of to-do list

        Task& task = tasks[taskNum - 1]; //dengan input arahkan menjadi task yang dimaksud
        task.Completeness = true; //mengubah "On-going" menjadi "Completed"
        cout << "Task marked as done!\n\n";
        cout << "===============================\n\n";

    } while (taskNum <= 0 || taskNum > tasks.size());
}





//=================== MAIN PROGRAM ==========================

int main() 
{
    vector<Task> tasks; //memasukkan vector Task dalam program
    char choice; //pilihan utama. saya memilih char untuk menghindari error saat menginput selain angka
    char choice1; //pilihan saat "view task"
    bool diff = true, choiceDefined = true; //untuk mengulang input jika input choice dan choice1 tidak valid

    do 
    {
        cout << "Todo List Menu:\n";
        cout << "1. Add Task\n";
        cout << "2. View Tasks\n";
        cout << "3. Delete Task\n";
        cout << "4. Mark Task as Complete\n";
        cout << "0. Exit\n";
//input choice untuk masuk ke fitur2
        cout << "Enter your choice: ";
        cin >> choice; 

        switch (choice) 
        {
//masuk ke fitur "Add Task"
            case '1':
                addTask(tasks); 
                break;
//masuk ke fitur "View Task"
            case '2':
                do
                {
                    //bisa memilih menampilkan keseluruhan atau hanya on-going
                    cout<<"\n\na. See the whole list\n";
                    cout<<"b. See on-going list\n";
                    cout<<"Choose : ";
                    cin>>choice1;
                    if (choice1 == 'a' || choice1 == 'A') 
                    {
                        //fitur View Task secara keseluruhan
                        viewTaskfull(tasks);
                        diff = true;
                    }
                    else if (choice1 == 'b' || choice1 == 'B')
                    {
                        //fitur untuk melihat on-going saja (fitur tambahan)
                        viewTaskgoing(tasks);
                        diff = true;
                    }
                    else diff = false;
                } while (diff == false);
                break;
//masuk ke fitur "Delete Task"
            case '3':
                delTask(tasks);
                break;
//masuk ke fitur "Mark Task as Done"
            case '4':
                markTask(tasks);
                break;
//jika pilih 0, keluar dari program
            case '0':
                cout << "===============\nTerima Kasih...\n";
                break;
//jika kita pilih selain 0-4, akan terjadi error
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }

        cout << endl;
    }
    while (choice != '0'); //selama tidak memasukkan 0 (keluar), maka akan terus berulang.
    return 0;
}