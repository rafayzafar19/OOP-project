#include<iostream>
#include<string>
#include<vector>
#include<limits>
#include<stdexcept>
#include<fstream>
#include<algorithm>
#include <ranges>
#include <sstream>
//#include<string.h>
using namespace std;

class customexp : public exception{
	public:
		const char* whaterp(){
			return "  *INCORRECT ERP FORMAT*(ERP_EXCEPTION_THROWN)";
		}
		const char* pass(){
			return "  INCORRECT PASSWORD FORMAT*(PW_EXCEPTION_THROWN) ";
		}
};
class student;
class courselist{
    public:
    string arr_pe_courselist[6]={"CAL-2","STATISTICS","OOP","SPEECH COMM","PHYSICS","DISCRETE MATHS"};
    string arr_bio_courselist[6]={"CHEMISTRY","GENETICS","MOLECULAR-BIOLOGY","SPEECH COMM","PHYSICS","ECOLOGY"};
    string arr_com_courselist[6]={"ECONOMICS","ACCOUNTING-1","FINANCE","SPEECH COMM","B-MATHS","TAXATION"};
    string arr_ss_courselist[6]={"HISTORY","LAW-1","INL-RELATIONS","SPEECH COMM","PUBLIC ADMINSTRATION","SOCIOLOGY-1"};
    string arr_courselist[3]={"SPEECH COMM","COLLEGE-ALGEBRA","CRW"};
    public:
    virtual void displaycourses(student &x)=0;
};


class student : public courselist {
public:
    string studentname;
    int erpno;
    int batchyear;
    string passw;
    vector<string>courses;
    string background;
    double gpa;



public:
    student(){}

    student(string s,int e,int b,string p,string bg,double g){
        studentname=s;
        erpno=e;
        batchyear=b;
        passw=p;
        background=bg;
        gpa=g;
    }

    void displaycourses(student &x){
        cout << "  CURRENT ENROLLED COURSES: " << endl;
        for(int i=0;i<courses.size();i++){
            if(!courses[i].empty()){
                cout << i+1 << "." << courses[i] << endl;
            }
        }
    }

    void addclass(student &s) {
        cout << "  YOUR RECOMMENDED COURSE LIST: " << endl;

        auto crslist = [](string x[]){
            for(int i=0; i<6; i++){
                cout << i+1 << "." << x[i] << endl;
            }
        };

        if(s.background == "Pre-engineering"){
            crslist(arr_pe_courselist);
        }
        else if(s.background == "Social-sciences"){
            crslist(arr_ss_courselist);
        }
        else if(s.background == "Biology"){
            crslist(arr_bio_courselist);
        }
        else if(s.background == "Commerce"){
            crslist(arr_com_courselist);
        }

        int i = 0;
        int choice;
        while(true){
            int choice;
            if (courses.size() >= 6) {
                cout << "  *CLASS LIMIT REACHED* " << endl;
                break;
            }
            while(true) {
                cout << "  ENTER CLASS TO ADD(-1 to end input): " << endl;
                if (cin >> choice) {
                    break;
                } else {
                    cout << "  *INVALID INPUT* " << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
            }


            if(choice == -1){
                break;
            }
            else if(choice >= 1 && choice <= 6){
                string selectedCourse;

                if(s.background == "Pre-engineering"){
                    selectedCourse = arr_pe_courselist[choice - 1];
                }
                else if(s.background == "Social-sciences"){
                    selectedCourse = arr_ss_courselist[choice - 1];
                }
                else if(s.background == "Biology"){
                    selectedCourse = arr_bio_courselist[choice - 1];
                }
                else if(s.background == "Commerce"){
                    selectedCourse = arr_com_courselist[choice - 1];
                }

                bool alreadyAdded = false;
                for(int j = 0; j < s.courses.size(); j++){
                    if(courses[j] == selectedCourse){
                        alreadyAdded = true;
                        break;
                    }
                }

                if(alreadyAdded){
                    cout << "  Class '" << selectedCourse << "' is already added." << endl;
                }
                else{
                    courses.push_back(selectedCourse);
                    cout << "  Class '" << selectedCourse << "' added successfully." << endl;
                }
            }
            else{
                cout << "  *INVALID CHOICE* " << endl;
            }
        }
    }




    void removeclass() {
        if (courses.empty()) {
            cout << "  *NO CLASSES REGISTERED* " <<endl;
            return;
        }

        string classToRemove;
        cout << "  ENTER CLASS TO REMOVE: " <<endl;
        cin >> classToRemove;

        auto it = find(courses.begin(), courses.end(), classToRemove);

        if (it != courses.end()) {
            courses.erase(it);
            cout << "  *CLASS REMOVED* " <<endl;
        } else {
            cout << "  *CLASS NOT FOUND* " <<endl;
        }
    }


    void displayrecord(student &rec){
        student s=rec;
        cout << "  Name: " << s.studentname << endl;
        cout << "  ERP: " << s.erpno << endl;
        cout << "  GPA: " << s.gpa << endl;
        cout << "  Batch of " << s.batchyear << endl;
        cout << "  Students academic background: " << s.background << endl;

    }


    void s_features(student &s,vector<student> &v) {


        while(true){

            int c;
            while (true) {
                cout << "--------STUDENT MENU--------" << endl;
                cout << endl;
                cout << "  1. ADD CLASSES  " <<endl;
                cout << "  2. REMOVE CLASSES  " <<endl;
                cout << "  3. DISPLAY RECORD  " <<endl;
                cout << "  4. DISPLAY CLASSES  " <<endl;
                cout << "  5. LOGOUT  " <<endl;
                if (cin >> c) {
                    break;
                } else {
                    cout << "  *INVALID INPUT* " << std::endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
            }
            switch(c){
                case 1:
                    s.addclass(s);

                break;
                case 2:
                    s.removeclass();

                break;
                case 3:
                    s.displayrecord(s);

                break;
                case 4:
                    s.displaycourses(s);

                break;
                case 5:
                    v.push_back(s);
                    break;
                default:
                    cout << "  *INVALID INPUT* " << endl;
                break;
            }

            if(c==5){
                break;

            }
        }

    }

    friend ostream& operator<<(ostream& os, const student& s) {
        os << s.studentname << "," << s.erpno << "," << s.gpa << "," << s.batchyear << "," << s.passw << "," << s.background;
        for (const auto& course : s.courses) {
            os << "," << course;
        }
        return os;
    }

    friend istream& operator>>(istream& is, student& s) {
        string line;
        if (getline(is, line)) {
            istringstream ss(line);
            getline(ss, s.studentname, ',');
            ss >> s.erpno;
            ss.ignore();
            ss >> s.gpa;
            ss.ignore();
            ss >> s.batchyear;
            ss.ignore();
            getline(ss, s.passw, ',');
            getline(ss, s.background, ',');

            s.courses.clear();
            string course;
            while (getline(ss, course, ',')) {
                s.courses.push_back(course);
            }
        }
        return is;
    }

    ~student(){}

};

struct sortedbyname {
    bool operator() (student &obj1,student &obj2) {
        return obj1.studentname<obj2.studentname;
    }
};

struct sortedbyerp {
    bool operator() (student &obj1,student &obj2) {
        return obj1.erpno<obj2.erpno;
    }
};


class admin: public courselist{
    public:
    string adminname;
    string passw;


    public:
      admin(){}
      admin(string n,string p){
    adminname=n;
    passw=p;
    }


    void displaycourses(student & x){


    cout << "  ENROLLED COURSES: " << endl;
    for(int i=0;i<x.courses.size();i++){
        if(!x.courses[i].empty()){
        cout << i+1 << "." << x.courses[i] << endl;
        }
    }
    }

  void addclass(student &x) {
    cout << "  YOUR RECOMMENDED COURSE LIST: " << endl;

    auto crslist = [](string x[]){
        for(int i=0; i<6; i++){
            cout << i+1 << "." << x[i] << endl;
        }
    };

     if(x.background == "Pre-engineering"){
        crslist(arr_pe_courselist);
    }
    else if(x.background == "Social-sciences"){
        crslist(arr_ss_courselist);
    }
    else if(x.background == "Biology"){
        crslist(arr_bio_courselist);
    }
    else if(x.background == "Commerce"){
        crslist(arr_com_courselist);
    }

    int i = 0;

    while(true){
        int choice;
        if (x.courses.size() >= 6) {
            cout << "  *CLASS LIMIT REACHED* " << endl;
            break;
        }
        while(true) {
            cout << "  ENTER CLASS TO ADD(-1 to end input): " << endl;
            if (cin >> choice) {
                break;
            } else {
                cout << "  *INVALID INPUT* " << std::endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }

        if(choice == -1){
            break;
        }
        else if(choice >= 1 && choice <= 6){
            string selectedCourse;

            if(x.background == "Pre-engineering"){
                selectedCourse = arr_pe_courselist[choice - 1];
            }
            else if(x.background == "Social-sciences"){
                selectedCourse = arr_ss_courselist[choice - 1];
            }
            else if(x.background == "Biology"){
                selectedCourse = arr_bio_courselist[choice - 1];
            }
            else if(x.background == "Commerce"){
                selectedCourse = arr_com_courselist[choice - 1];
            }

            bool alreadyAdded = false;
            for(int j = 0; j < x.courses.size(); j++){
                if(x.courses[j] == selectedCourse){
                    alreadyAdded = true;
                    break;
                }
            }

            if(alreadyAdded){
                cout << "  Class '" << selectedCourse << "' is already added." << endl;
            }
            else{
                x.courses.push_back(selectedCourse);
                cout << "  Class '" << selectedCourse << "' added successfully." << endl;
            }
        }
        else{
            cout << "  *INVALID CHOICE* " << endl;
        }
    }
          return;
}



    void removeclass(student &x) {
          if (x.courses.empty()) {
              cout << "  *NO CLASSES REGISTERED* " <<endl;
              return;
          }

          string classToRemove;
          cout << "  ENTER CLASS TO REMOVE: " <<endl;
          cin >> classToRemove;

          auto it = find(x.courses.begin(), x.courses.end(), classToRemove);

          if (it != x.courses.end()) {
              x.courses.erase(it);
              cout << "  *CLASS REMOVED* " <<endl;
          } else {
              cout << "  *CLASS NOT FOUND* " <<endl;
          }
          return;
      }

   void editrecord(student &x){
   while(true){
    int c;
    while (true) {
        cout << "--------EDIT RECORD MENU--------" << endl;
        cout << endl;
        cout << "  1. CHANGE NAME  " << endl;
        cout << "  2. CHANGE ERP  " << endl;
        cout << "  3. CHANGE BATCH  " << endl;
        cout << "  4. ACCOUNT LOGIN PASSWORD  " << endl;
        cout << "  5. CHANGE STUDENT ACADEMIC BACKGROUND  " << endl;
        cout << "  6. UPDATE GPA   " << endl;
        cout << "  7. BACK  " << endl;
        if (cin >> c) {
            break;
        } else {
            cout << "  *INVALID INPUT, TRY AGAIN* " << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
   switch(c){
    case 1:
    {
    string n;
        cin.ignore();
        cout << "  ENTER NEW NAME: " << endl;
        getline(cin,n);
    x.studentname=n;
    cout << "  *NEW NAME SAVED* " << endl;
    break;
    }
    case 2:
    {
    int e=0;
        int e2=0;

    int count=0;
    try{
        while (true) {
        cout << "  ENTER NEW ERP(must be 5 digits): " << endl;

        if (cin >> e) {

            break;
        } else {
            cout << "Invalid input. ERP is an integer." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
        e2 = e;
        count = 0;
        while(e2 > 0){
            e2 = e2 / 10;
            count++;
        }
    if(count!=5){
     throw customexp();
    }
        else {
            x.erpno=e;
        }
    }
   catch(customexp &s){
    cout << s.whaterp() << endl;

   }
    break;
    }
    case 3:
   {
    int e;
    try {
        while (true) {
            cout << "  ENTER NEW BATCH YEAR: " << endl;
            if (cin >> e) {
                break;
            } else {
                cout << "Invalid input. BATCH YEAR is an integer." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
        if(e>2023 && e<2028) {
            x.batchyear=e;
            cout << "  *BATCH YEAR UPDATED* " << endl;
            break;
        }
        else {
            throw "  Batch year not in range(2024-2027)";
        }
    }
        catch(const char* &by){
            cout << by << endl;
            break;
        }



   }
    case 4:
    {
    string p;
    string temp;
    	try{


    	bool num=false;
        cout << "  ENTER NEW PASSWORD(has to be greater than 4 characters and contain no numbers): " << endl;
        cin >> temp;
        if(temp.length() > 4){
        	for(auto i : temp){
        		if(isdigit(i)){
        			num=true;
				}
			}
		}
		else{
			throw customexp();
			continue;
		}
		if(num){
			throw customexp();
			continue;
		}
		else{
			p=temp;
		}
	x.passw=p;
    cout << "  *PASSWORD CHANGED* " << endl;
	}
	catch(customexp & x){
		cout << x.pass() << endl;
	}

    break;
    }
    case 5:
	{
	  int bgc;
    while (true) {
        cout << "  ENTER STUDENT BACKGROUND: " << endl;
        cout << "  1. Pre-engineering " << endl;
        cout << "  2. Social-sciences " << endl;
        cout << "  3. Commerce " << endl;
        cout << "  4. Biology " << endl;
        if (cin >> bgc) {
            break;
        } else {
            cout << "Invalid input." << std::endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
   switch(bgc){
   	case 1:{
   		x.background="Pre-engineering";
		break;
	   }
	case 2:{
		x.background="Social-sciences";
		break;
	}
	case 3:{
		x.background="Commerce";
		break;
	}
	case 4:{
		x.background="Biology";
		break;
	}
	default:{
		cout << "Invalid input" << endl;
		break;
	}
   }
		break;
	}
    case 6: {
        double g=0;
        try{
            while (true) {
                cout << "  ENTER NEW GPA: " << endl;
                if (cin >> g) {

                    break;
                } else {
                    cout << "  Invalid input. GPA is a double." << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
            }

            if(g>4.0 || g<2.2){
                throw "  GPA is not in allowed range(2.2-4.0) ";
            }
            else {
                x.gpa=g;
            }
        }
        catch(const char* &msg){
            cout << msg << endl;
            break;
        }
    }
    case 7:
    	{
    	break;
		}
    default:
    {
        cout << "Invalid input" << endl;
        break;
    }
}
if(c==7){
	break;
}
   }
          return;
   }



   void a_displayrecord(student & x){
      student s=x;
    cout << "  Name: " << s.studentname << endl;
    cout << "  ERP: " << s.erpno << endl;
    cout << "  GPA: " << s.gpa << endl;
    cout << "  Batch of " << s.batchyear << endl;
    cout << "  Students academic background: " << s.background << endl;
    }

    student search(vector<student> &v){
        int e;
          student stu;
        cout << "  ENTER ERP OF STUDENT:" << endl;
        cin >> e;
        auto it = find_if(v.begin(),v.end(),[e](student &obj){ return obj.erpno==e;});
        for(int i=0;i<v.size();i++){
            if(v[i].erpno==e){
                stu = v[i];
                if(it!=v.end()) {
                    v.erase(it);
                }
                return stu;
            }
        }
        return student();
     }

void addnewrecord(vector<student> &v){
    string n;
    int e;
    int e2;
    int b;
    int b2;
    string p;
    string g;
    int count;
    double gp;
    double gp2;
    cout << "--------ADD NEW RECORD--------" << endl;
          cout << endl;
    while (true) {
    	cin.ignore();
        cout << "  ENTER STUDENT NAME: ";
        getline(cin,n);
        if(!n.empty()){
        cout << "  CONFIRM: " << n << " ->(yes/no): ";
        string confirm;
        cin >> confirm;
        if (confirm == "yes") {
            break;
        }
    }
    else{
    	cout << "  *EMPTY INPUT*" << endl;
    	continue;
	}
    }

while (true) {
    try {


        while (true) {

        cout << "  ENTER STUDENT ERP: ";
        if (cin >> e) {

            break;
        } else {
            cout << "  *INVALID INPUT, ERP SHOULD BE AN INTEGER* " << std::endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
            e2 = e;
            count = 0;
            while(e2 > 0){
                e2 = e2 / 10;
                count++;
            }
            if(count != 5){
                throw customexp();
            }
            cout << "  CONFIRM: " << e << " ->(yes/no): ";
            string confirm;
            cin >> confirm;
            if (confirm == "yes") {
                break;
            }
        }

    catch(customexp &s) {
        cout << s.whaterp() << endl;
    }
}
          while (true) {
              try{
                      while (true) {
                          cout << "    ENTER GPA: " << endl;
                          if (cin >> gp) {

                              break;
                          } else {
                              cout << "  Invalid input. GPA is a double." << endl;
                              cin.clear();
                              cin.ignore(numeric_limits<streamsize>::max(), '\n');
                          }
                      }

                      if(gp>4.0 || gp<2.2){
                          throw "  GPA is not in allowed range(2.2-4.0) ";
                      }
                  cout << "  CONFIRM: " << gp << " ->(yes/no): ";
                  string confirm;
                  cin >> confirm;
                  if (confirm == "yes") {
                      gp2=gp;
                      break;
                  }

              }
              catch(const char* &msg){
                  cout << msg << endl;
              }
          }
    while (true) {
        try {
            while (true) {
                cout << "  ENTER BATCH YEAR: " << endl;
                if (cin >> b) {
                    break;
                } else {
                    cout << "Invalid input. BATCH YEAR is an integer." << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
            }
            if(b>2023 && b<2028) {
                cout << "  CONFIRM: " << b << " ->(yes/no): ";
                string confirm;
                cin >> confirm;
                if (confirm == "yes") {
                    b2=b;
                    break;
                }
            }
            else {
                throw "  Batch year not in range(2024-2027)";
            }
        }
        catch(const char* &by){
            cout << by << endl;
        }
    }

    while (true) {

			string temp;
			try{
		bool num=false;
        cout << "  ENTER PASSWORD FOR STUDENT ACCOUNT(*has to be greater than 4 characters and contain no numbers*): " << endl;
        cin >> temp;
        if(temp.length() > 4){
        	for(auto i : temp){
        		if(isdigit(i)){
        			num=true;
				}
			}
		}
		else{
			throw customexp();
			continue;
		}
		if(num){
			throw customexp();
			continue;
		}
		else{
			p=temp;
		}
	cout << "  CONFIRM: " << p << " ->(yes/no): ";
        string confirm;
        cin >> confirm;
        if (confirm == "yes") {
            break;
        }

	}
	catch(customexp & x){
		cout << x.pass() << endl;
	}

    }

    while (true) {
          int bgc;
    while (true) {
        cout << "  ENTER STUDENT BACKGROUND: " << endl;
        cout << endl;
        cout << "  1. Pre-engineering " << endl;
        cout << "  2. Social-sciences " << endl;
        cout << "  3. Commerce " <<endl;
        cout << "  4. Biology " << endl;
        if (cin >> bgc) {
            break;
        } else {
            cout << "INVALID INPUT, TRY AGAIN " << std::endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
        switch(bgc){
            case 1:
                g="Pre-engineering";
                break;
            case 2:
                g="Social-sciences";
                break;
            case 3:
                g="Commerce";
                break;
            case 4:
                g="Biology";
                break;
            default:
                cout << "  *INVALID INPUT*" << endl;
                continue;
        }

        cout << "  CONFIRM: " << g << " ->(yes/no): ";
        string confirm;
        cin >> confirm;
        if (confirm == "yes") {
            break;
        }
    }

    v.push_back(student(n, e, b2, p, g,gp2));
}
    void displayall(vector<student> &v) {
          int c;
          while (true) {
              cout << "--------HOW TO DISPLAY?--------" << endl;
              cout <<endl;
              cout << "  1. DISPLAY BY NAME  " << endl;
              cout << "  2. DISPLAY BY ERP  " << endl;
              if (cin >> c) {
                  break;
              }
              else {
                  cout << "  *INVALID INPUT, TRY AGAIN* " << std::endl;
                  cin.clear();
                  cin.ignore(numeric_limits<streamsize>::max(), '\n');
              }
          }
          if(c==1) {
              cout << "--------ALL SAVED RECORDS(SORTED BY NAME)--------" << endl;
              cout << endl;
              sortedbyname obj;
              int count=1;
              ranges::sort(v,obj);
              for(auto s:v) {
                  cout << "  RECORD "<<count<<": " << endl;
                  cout << endl;
                  cout << "  Name: " << s.studentname << endl;
                  cout << "  ERP: " << s.erpno << endl;
                  cout << "  GPA: " << s.gpa << endl;
                  cout << "  Batch of " << s.batchyear << endl;
                  cout << "  Students academic background: " << s.background << endl;
                  cout << endl;
                  count++;
              }

          }
          else if(c==2) {
              cout << "--------ALL SAVED RECORDS(SORTED BY ERP)--------" << endl;
              cout << endl;
              sortedbyerp obj;
              int count=1;
              sort(v.begin(),v.end(),obj);
              for(auto s:v) {
                  cout << "  RECORD "<<count<<": " << endl;
                  cout << endl;
                  cout << "  Name: " << s.studentname << endl;
                  cout << "  ERP: " << s.erpno << endl;
                  cout << "  GPA: " << s.gpa << endl;
                  cout << "  Batch of " << s.batchyear << endl;
                  cout << "  Students academic background: " << s.background << endl;
                  cout << endl;
                  count++;
              }
          }
          else {
              cout << "  *INVALID INPUT* " << endl;
          }
      }

void a_features(admin &a,vector<student> &v){

          while(true){

        int z = 0;
      while (true) {
        cout << "--------ADMIN MENU--------" <<endl;
          cout << endl;
        cout << "  1. ADD NEW STUDENT RECORD  " << endl;
        cout << "  2. EDIT EXISTING STUDENT RECORD  " << endl;
        cout << "  3. DISPLAY ALL STUDENT RECORDS  " << endl;
        cout << "  4. REMOVE EXISTING STUDENT RECORD  " << endl;
        cout << "  5. LOGOUT  " << endl;
        if (cin >> z) {
            break;
        } else {
            cout << "  *INVALID INPUT, TRY AGAIN* " << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
      }
        if(z==5){
        	break;
		}
        else if(z==1){
         a.addnewrecord(v);
        }

        else if(z==3) {
            a.displayall(v);
        }
        else if(z==4) {
            cout << "--------RECORD REMOVAL--------" << endl;
            cout << endl;
            int e;
            while(true) {
                cout << "  ENTER ERP OF STUDENT:" << endl;
                if (cin >> e) {
                    break;
                } else {
                    cout << "  Invalid input. ERP is an integer." << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
            }
           auto it = find_if(v.begin(),v.end(),[e](student &s){ return s.erpno==e;});
            if(it != v.end()) {
                v.erase(it);
                cout << "  *RECORD REMOVED*" << endl;
            }
            else {
                cout << "  *ERP NOT FOUND*" << endl;
            }

        }

        else if(z==2){
        student s=a.search(v);
            if(s.studentname=="") {
                cout << "  *INVALID ERP* " << endl;
                continue;
            }

        while (true){
            int c;


    while (true) {
        cout << "--------STUDENT RECORD MENU--------" << endl;
        cout << endl;
        cout << "  1. ADD CLASSES  " << std::endl;
        cout << "  2. REMOVE CLASSES  " << std::endl;
        cout << "  3.  DISPLAY RECORD  " << std::endl;
        cout << "  4.  DISPLAY CLASSES  " << std::endl;
        cout << "  5.  EDIT RECORD  " << std::endl;
        cout << "  6.  BACK  " << std::endl;
        if (std::cin >> c) {
            break;
        } else {
            cout << "  *INVALID INPUT, TRY AGAIN* " << std::endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
        switch(c){
            case 1:
            a.addclass(s);
            break;
            case 2:
            a.removeclass(s);
            break;
            case 3:
            a.a_displayrecord(s);
            break;
            case 4:
            a.displaycourses(s);
            break;
            case 5:
            a.editrecord(s);
            break;
            case 6:
                v.push_back(s);
            break;

            default:
            cout << "  *INVALID INPUT* " << endl;
            break;
        }
        if(c==6){
        	break;
		}
        }

        }
        else{
            cout << "  *INVALID INPUT, TRY AGAIN* " << endl;

        }


}
}

  ~admin(){}

   };



class user:public admin,public student{
public:

    // student validation functions

    student validate(int x,string y, vector<student> &v){
        for(int i=0;i<v.size();i++){
        if(x==v[i].erpno){
            if(y==v[i].passw){
                return v[i];
                break;
            }
        }
    }

    return student();
    }

    student currentstudent(vector<student> &v) {
        cout << "--------STUDENT LOGIN--------" << endl;
        cout << endl;
        int e;
        string pss;
        cout << "    ENTER YOUR ERP:" << endl;
        cin >> e;
        cout << "    ENTER YOUR PASSWORD:" << endl;
        cin >> pss;
        auto it=find_if(v.begin(),v.end(),[e](student &ob){ return ob.erpno==e;});
        student stu = validate(e, pss,v);
        if(it!=v.end()) {
            v.erase(it);
        }

      if(stu.studentname==""){
       cout << "  *INVALID LOGIN DETAILS*" << endl;
       return student();
    }
    else{
        return stu;
    }

    }

    // admin validation functions

    admin currentadmin(vector<admin> &v){
        cout << "--------ADMIN LOGIN--------" << endl;
        cout << endl;
    string n;
    string pss;
    cout << "  ENTER ADMIN LOGIN NAME:" << endl;
    cin >> n;
    cout << "  ENTER ADMIN LOGIN PASSWORD:" << endl;
    cin >> pss;
    admin ad = a_validate(n, pss, v);
      if(ad.adminname==""){
       cout << "  *INVALID LOGIN DETAILS*" << endl;
       return admin();
    }
    else{
        return ad;
    }

    }

     admin a_validate(string x,string y, vector<admin> &v){
        for(int i=0;i<v.size();i++){
        if(x==v[i].adminname){
            if(y==v[i].passw){
                return v[i];
                break;
            }
        }
    }
    return admin();
    }

    void save_students(const vector<student>& students) {
        ofstream ofs("C:\\Users\\rafay\\OneDrive\\Desktop\\Working project file\\saved data 2.0.txt");
        if (!ofs) {
            cerr << "Error opening file for writing." << endl;
            return;
        }

        for (const auto& s : students) {
            ofs << s << endl;
        }

        ofs.close();
    }

    void load_students(vector<student>& students) {
        ifstream ifs("C:\\Users\\rafay\\OneDrive\\Desktop\\Working project file\\saved data 2.0.txt");
        if (!ifs) {
            cerr << "Error opening file for reading." << endl;
            return;
        }

        students.clear();
        student s;
        while (ifs >> s) {
            students.push_back(s);
        }

        ifs.close();
    }

    ~user(){}

};







  int main() {
   user obj;
   vector <student> studentlist;
   obj.load_students(studentlist);
  //test data:student("Muhammad Rafay Zafar",29014,2027,"rafay@iba","Biology",3.6),student("Ahmed Hassan Khan",29015,2027,"ahmed@iba","Commerce",3.2),student("Muhammad Anis",29017,2027,"anis@iba","Social-sciences",3.4)
   vector <admin> adminlist={ admin("Adminiba", "admin@iba")};



  while(true){
   int g;
    while (true) {
        cout << "--------RAFAY'S STUDENT MANAGEMENT SYSTEM--------" << endl;
        cout << endl;
        cout << "         1. ADMIN LOGIN " << endl;
        cout << "         2. STUDENT LOGIN " << endl;
        cout << "         3. DISPLAY DEANS LIST " << endl;
        cout << "         4. END PROGRAM " << endl;
        cout << "         (ENTER 1-3 TO PROCEED) " << endl;
        if (cin >> g) {
            break;
        }
        else {
            cout << "INVALID INPUT, TRY AGAIN " << std::endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
  switch(g){
    case 1:
    {
    admin temp;
    user obj;
    admin ad;
    while (ad.adminname.empty()) {
        ad = obj.currentadmin(adminlist);
        if (!ad.adminname.empty()) {
            break;
        }
    }
    while (true) {
        temp.a_features(ad,studentlist);
        string choice;
        cout << "      Do you wish to exit?(yes or no)" << endl;
        cin >> choice;
        if (choice == "yes") {
            break;
        }
        else if (choice != "no") {
            cout << "      *INVALID CHOICE* " << endl;
        }
    }
    break;
    }
    case 2:
    {
    student temp;
    user obj;
    student ad;
    while (ad.studentname.empty()) {
        ad = obj.currentstudent(studentlist);
        if (!ad.studentname.empty()) {
            break;
        }
    }
    while (true) {
        temp.s_features(ad,studentlist);
        string choice;
        cout << "         Do you wish to exit?(yes or no)" << endl;
        cin >> choice;
        if (choice == "yes") {
            break;
        }
        else if (choice != "no") {
            cout << "      *INVALID CHOICE* " << endl;
        }
    }
    break;
    }
      case 3:
    {
        int count=1;
        cout << "--------DEANS LIST--------" << endl;
        cout << endl;
        auto deanslist_view = studentlist | std::ranges::views::filter([](const student &obj){ return obj.gpa>3.5;});
        vector<student> deanslist(deanslist_view.begin(), deanslist_view.end());
        sort(deanslist.begin(),deanslist.end(),[](student &ob1,student &ob2){ return ob1.gpa>ob2.gpa;});
        for(auto m:deanslist) {
            cout << "  STUDENT " <<count<<":"<<endl;
            cout << "  Name: " << m.studentname << endl;
            cout << "  GPA: " << m.gpa << endl;
            count++;
        }

        break;
    }


      case 4: {
        obj.save_students(studentlist);
        return 0;
    }
    default:
    	{
    		cout << "         INVALID INPUT, TRY AGAIN. " << endl;

		}
   }

}
return 0;
  }
