#include <iostream>
#include <string>
#include <windows.h>
#include <fstream>
using namespace std;
bool modified=false;
int sharpened[12],flatened[12];
int spl=0,ftl=0;

int sounds[7][12] = {
    { 33,35,37,39,41,44,46,49,52,55,58,62 },
    { 65,69,73,78,82,87,92,98,104,110,117,123 },
    { 131,139,147,156,165,175,185,196,208,220,233,247 },
    { 262,277,294,311,329,349,370,392,415,440,466,494 },
    { 523,554,587,622,659,698,740,784,831,880,932,988 },
    { 1047,1109,1175,1245,1319,1397,1480,1568,1661,1760,1865,1976 },
    { 2093,2217,2349,2489,2637,2794,2960,3135,3322,3520,3729,3951 }
};

int get_note_id(string f) {
    if (f == "do") {
        return 0;
    }
    else if (f == "do#") {
        return 1;
    }
    else if (f == "re") {
        return 2;
    }
    else if (f == "re#") {
        return 3;
    }
    else if (f == "mi") {
        return 4;
    }
    else if (f == "fa") {
        return 5;
    }
    else if (f == "fa#") {
        return 6;
    }
    else if (f == "so") {
        return 7;
    }
    else if (f == "so#") {
        return 8;
    }
    else if (f == "la") {
        return 9;
    }
    else if (f == "la#") {
        return 10;
    }
    else if (f == "si") {
        return 11;
    }
    else {
        return -1;
    }
}

int get_length(int fnote_length, int note) {
    switch (note) {
        case 128:
            return fnote_length / 32;
            break;
        case 64:
            return fnote_length / 16;
            break;
        case 32:
            return fnote_length / 8;
            break;
        case 16:
            return fnote_length / 4;
            break;
        case 8:
            return fnote_length / 2;
            break;
        case 4:
            return fnote_length;
            break;
        case 2:
            return fnote_length * 2;
            break;
        case 1:
            return fnote_length * 4;
            break;
        default:
            return -1;
            break;
    }
}

int identify_and_get_sum(int fnote_length, string ide) {
    ide=ide+"-";
    int hyphen_index = 0, sum = 0;
    for (unsigned int i = 1; i<ide.length(); i += 1) {
        if (ide[i] == '-') {
            if (hyphen_index == 0) {
                hyphen_index = i;
                sum += get_length(fnote_length, atoi(ide.substr(0, i).c_str()));
            }
            else {
                sum += get_length(fnote_length, atoi(ide.substr(hyphen_index + 1, i - hyphen_index - 1).c_str()));
            }
        }
    }
    if (hyphen_index == 0) {
        return get_length(fnote_length, atoi(ide.c_str()));
    } else {
        return sum;
    }
}

void reg_note(string m){
    string a[12];
    short items=0;
    m=m+" ";
    int space_index = 0;
    for (unsigned int i = 1; i<m.length(); i += 1) {
        if (m[i] == ' ') {
            if (space_index == 0) {
                space_index = i;
                a[items]=m.substr(0, i);
                items+=1;
            }else {
                a[items]=m.substr(space_index + 1, i - space_index - 1);
                items+=1;
            }
        }
    }
    if(items==0){
    	return;
    }
    memset(sharpened,0,12*sizeof(int));
    memset(flatened,0,12*sizeof(int));
    ftl=0,spl=0;
    for(int i=0;i<items;i+=1){
        int u=get_note_id(a[i].substr(0,a[i].length()-1));
        if(a[i][a[i].length()-1]=='+'){
            sharpened[spl]=u;
            spl+=1;
        }else{
            flatened[ftl]=u;
            ftl+=1;
        }
    }
    modified=true;
}

bool isResume(string &se){
    if(se[se.length()-1]=='R'){
        se=se.substr(0,se.length()-1);
        return true;
    }
    return false;
}

bool contains(int arr[],int arr_len,int result){
    bool cts=false;
    for(int i=0;i<arr_len;i+=1){
        if(i==result){
            cts=true;
            break;
        }
    }
    return cts;
}

int main(int argc, char *argv[])
{
    string infile;
    if (argc<2) {
        cout << "Please enter input file path (absolute path): " << endl;
        cin >> infile;
    } else {
        infile = argv[1];
    }
    ifstream fin(infile.c_str());
    string output_name;
    int fnote_length;
    fin >> output_name >> fnote_length;
    ofstream fout(output_name.c_str());
    
    string note_type, sound_type;
    int height,clap=0,ctr=0;
    while (fin >> note_type) {
        if (note_type.substr(0, 2) == "//") {
            continue;
        }
        if(note_type.substr(0,2)=="el"){
            fout<<endl;
            cout<<"Strated new line"<<endl;
            continue;
        }
        if(note_type.substr(0,2)=="pr"){
            string m;
            getline(fin,m);
            m=m.substr(1);
            fout<<m<<endl;
            cout<<"Printed \""<<m<<"\" to file"<<endl;
            continue;
        }
        if(note_type.substr(0,4)=="clap"){
            fin>>clap;
            ctr=0;
            continue;
        }
        if(note_type.substr(0,3)=="reg"){
            string m;
            getline(fin,m);
            m=m.substr(1);
            if(m=="clear"){
                modified=false;
            }else{
            	reg_note(m);
			}
			continue;
        }
        fin >> sound_type;
        int sum = identify_and_get_sum(fnote_length, note_type);
        if (sound_type == "br") {
            fout << "Sleep(" << sum << ");" << endl;
            cout << "Identified "<<note_type<<"th break note" << endl;
            continue;
        }
        fin >> height;
        bool res=isResume(sound_type);
        int drmf = get_note_id(sound_type);
        if (drmf == -1) {
            cout << "Error: Invaild note" << endl;
            continue;
        }
        if (sum <= 0) {
            cout << "Error: Can't identify time" << endl;
            continue;
        }
        
        if(modified&&(!res)){
            if(contains(sharpened,spl,drmf)){
                drmf+=1;
                if(drmf==8){
                    height+=1;
                    drmf=0;
                }
                cout<<"Sound sharpened"<<endl;
            }
            if(contains(flatened,ftl,drmf)){
                drmf-=1;
                if(drmf==0){
                    height-=1;
                    drmf=11;
                }
                cout<<"Sound flatened"<<endl;
            }
        }

        fout << "Beep(" << sounds[height][drmf] << "," << sum << ");" << endl;
        cout << "Identified " << note_type << "th note " << sound_type << endl;

        if(clap!=0){
            ctr+=sum;
            if(ctr>=fnote_length*clap){
                fout<<endl;
                ctr=0;
            }
        }
    }
    cout << "Finish, saved as "<<output_name << endl;
    system("pause>nul");
    return 0;
}

