#include <iostream>
#include <string>
#include <windows.h>
#include <fstream>
using namespace std;
int sounds[7][12] = {
    { 33,35,37,39,41,44,46,49,52,55,58,62 },
    { 65,69,73,78,82,87,92,98,104,110,117,123 },
    { 131,139,147,156,165,175,185,196,208,220,233,247 },
    { 262,277,294,311,329,349,370,392,415,440,466,494 },
    { 523,554,587,622,659,698,740,784,831,880,932,988 },
    { 1047,1109,1175,1245,1319,1397,1480,1568,1661,1760,1865,1976 },
    { 2093,2217,2349,2489,2637,2794,2960,3135,3322,3520,3729,3951 }
};

int get_note_id(std::string f) {
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

int identify_and_get_sum(int fnote_length, std::string ide) {
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
    int height;
    while (fin >> note_type) {
        if (note_type.substr(0, 2) == "//") {
            continue;
        }
        if(note_type.substr(0,2)=="el"){
            fout<<endl;
            cout<<"Strated new line"<<endl;
            continue;
        }
        if(note_type.substr(0,3)=="pr"){
            string m;
            getline(fin,m);
            m=m.substr(1);
            fout<<m<<endl;
            cout<<"Printed \""<<m<<"\" to file"<<endl;
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
        int drmf = get_note_id(sound_type);
        if (drmf == -1) {
            cout << "Error: Invaild note" << endl;
            continue;
        }
        if (sum <= 0) {
            cout << "Error: Can't identify time" << endl;
            continue;
        }
        fout << "Beep(" << sounds[height][drmf] << "," << sum << ");" << endl;
        cout << "Identified " << note_type << "th note " << sound_type << endl;
    }
    cout << "Finish, saved as "<<output_name << endl;
    system("pause>nul");
    return 0;
}
