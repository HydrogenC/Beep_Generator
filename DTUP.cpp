#include <iostream>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <windows.h>
using namespace std;

void slowprint(int interval, string me){
    for(int i;i<me.size();i+=1){
            cout<<me[i];
            Sleep(interval);
    }
}

void slowprintln(int interval, string me){
    slowprint(interval,me);
    cout<<endl;
}

void stopgame(){
    slowprintln(30,"你失败了，电脑将被全面入侵！");
    Sleep(1500);
    ExitProcess(0);
}

DWORD WINAPI Wait(LPVOID lpParameter)
{
    Sleep(*(int *)lpParameter);
    system("cls");
    slowprintln(30,"答题超时，电脑将被全面入侵！");
    Sleep(1500);
    ExitProcess(0);
}

struct filling{
    string question;
    string answer;
};

struct choosing{
    string question;
    string a;
    string b;
    string c;
    string d;
    char answer;
};

void printchoose(choosing e, int num){
    slowprint(40,"选择题：例题 ");
    cout<<num<<endl;
    slowprintln(30,e.question);
    slowprintln(30,"A. "+e.a);
    slowprintln(30,"B. "+e.b);
    slowprintln(30,"C. "+e.c);
    slowprintln(30,"D. "+e.d);
    slowprint(30,"你的选择：");
}

void printfill(filling e,int num){
    slowprint(40,"填空题：例题 ");
    cout<<num<<endl;
    slowprintln(30,e.question);
}

string list[6]={
    "您好，这是新型计算机木马",
    "请不要关闭本程序，不然会对您的计算机造成不可逆损伤",
    "为了考验您的智商，我们准备了一个测试",
    "答错或退出程序会对电脑造成不可逆损伤，请认真答题",
    "全部答对即可解除该病毒对您计算机的控制",
    "准备好了吗 (Y/N)"
};

choosing csi[5]={
    {"以下哪种计算机语言是Microsoft推出的？","Java","CSharp","C++","SQL",'B'},
    {"Windows NT 的第一个版本是什么？","WinNT 1.0","WinNT 2.1","WinNT 3.1","WinNT 4.0",'C'},
    {"强制关闭程序的CMD指令是？","taskmanager /kill","task /kill","taskill","taskkill",'D'},
    {"那个数的平方是19开头的？","44","13","46","42",'A'},
    {"C++ 中等待一段时间（精准到微秒）的方法是？","Sleep()","sleep()","usleep()","uSleep()",'C'}
};

filling fil[5]={
    {"FTP 的默认端口是：","21"},
    {"2的20次方是","1048576"},
    {"英特尔的竞争对手是？","AMD"},
    {"回归线的纬度（一位小数）？","23.5"},
    {"苹果的官方编程语言？","Obj-C"}
};

int main(){
    HANDLE h = GetStdHandle ( STD_OUTPUT_HANDLE );
    WORD wOldColorAttrs;
    CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
    GetConsoleScreenBufferInfo(h, &csbiInfo);
    wOldColorAttrs = csbiInfo.wAttributes;
    for(int i=0;i<6;i+=1){
            slowprintln(25,list[i]);
    }
    start: char y;
    cin>>y;
    switch(y){
        case 'Y':
            break;
        case 'N':
            slowprintln(30,"您有十秒钟准备时间，之后将开始挑战！");
            for(int i=9;i>=0;i-=1){
                cout<<"还有"<<i<<"秒...";
                Sleep(1000);
                cout<<"\b\b\b\b\b\b\b\b\b\b";
            }
            break;
        default:
            slowprintln(30,"输入错误，请重新输入" );
            goto start;
            break;
    }
    system("cls");
    slowprintln(30,"挑战开始！");
    slowprintln(30,"选择题每题 5 秒时间，填空题 10 秒，超时直接算答错");
    Sleep(600);
    system("cls");
    slowprintln(40,"第一部分：选择题");
    Sleep(600);
    for(int i=0;i<5;i+=1){
        system("cls");
        printchoose(csi[i],i+1);
        char asn;
        HANDLE hThread = CreateThread(NULL, 0, Wait, new int(5000), 0, NULL);
        cin>>asn;
        if(asn>96&&asn<123){
                asn-=32;
                }
        if(asn==csi[i].answer){
            TerminateThread(hThread,0);
            continue;
        }else{
            TerminateThread(hThread,0);
            system("cls");
            stopgame();
        }
    }
    slowprintln(40,"恭喜，选择题已全部完成！");
    Sleep(600);
    system("cls");
    slowprintln(40,"第二部分：填空题");
    Sleep(600);
    for(int i=0;i<5;i+=1){
        system("cls");
        printfill(fil[i],i+1);
        string asn;
        HANDLE hThread = CreateThread(NULL, 0, Wait, new int(10000), 0, NULL);
        cin>>asn;
        if(fil[i].answer==asn){
            TerminateThread(hThread,0);
            continue;
        }else{
            TerminateThread(hThread,0);
            system("cls");
            stopgame();
        }
    }
    slowprintln(40,"你成功了，此病毒将永远消失！");
    Sleep(2000);
    return 0;
}
