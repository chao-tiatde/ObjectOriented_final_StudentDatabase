#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

class STNODE {
    STNODE* ptr;
    string name;
    int no;
    int total;
    
public:
    // 建構子
    STNODE() : ptr(NULL), no(0){}
    STNODE(int no, string name) : no(no), name(name), ptr(NULL) {}
    virtual ~STNODE() {}

    // 資料存取函式
    void set_name(string s) { name = s; }
    void set_no(int n) { no = n; }
    
    int get_no() { return no; }
    string get_name() { return name; }
    virtual int get_total() { return 0; }

    void set_ptr(STNODE* p) { ptr = p; }
    STNODE* get_ptr() { return ptr; }
};
class PE: public STNODE{
	int run, swim, AI;
	static STNODE* head;
public:
	PE(int no = 0, string name = "", int run = 0, int swim = 0, int ai = 0): run(run), swim(swim), AI(ai), STNODE(no, name) {}
	// 運算子重載
    void operator+(int x) { run += x; swim += x; AI += x;}
    
	void set_run(int a) { run = a; }
    void set_swim(int b) { swim = b; }
    void set_AI(int c){ AI=c; }
    int get_run() { return run; }
    int get_swim() { return swim; }
    int get_AI() { return AI; }
    int get_total() { return (run + swim + AI); }
    // 靜態資料操作
    static STNODE*& get_head() { return head; }
	static void set_head(STNODE* p) { head = p; }

};
class CS: public STNODE{
	int prg, ing;
	static STNODE* head;
public:
	CS(int no = 0, string name = "", int ing = 0, int prg = 0): ing(ing), prg(prg), STNODE(no, name) {}
    void operator+(int x) { prg += x; ing += x; }
	
	void set_prg(int a) { prg = a; }
    void set_ing(int b) { ing = b; }
    int get_prg() { return prg; }
    int get_ing() { return ing; }
    int get_total() { return (prg + ing); }
    // 靜態資料操作
    static STNODE*& get_head() { return head; }
	static void set_head(STNODE* p) { head = p; }
};
class MENU {
    int select;
public:
    MENU() : select(1) {}

    void w_select(int x) { select = x; }
    int r_select() { return select; }
    void show() {
        cout << "\n選單MENU" << endl;
        cout << "1. 新增學生資料 Insertion" << endl;
        cout << "2. 查詢學生資料 Search" << endl;
        cout << "3. 刪除學生資料 Deletion" << endl;
        cout << "4. 調整學生成績 Update Grades" << endl;
        cout << "5. 列印串列資料 Print List Data" << endl;
        cout << "6. 列印學生成績單 Print Transcript" << endl;
        cout << "0. 離開 Exit" << endl;
        cout << "請輸入選擇項目？ Please select one: ";
    }
};

// 靜態變數初始化
STNODE* PE::head = NULL;
STNODE* CS::head = NULL;

//更新 
void save_all() {

	ofstream output("st.dat", ios::out);
	if (!output) {
		cout << "無法開啟檔案 st.dat" << endl;
		return;
	}

	STNODE* cur = PE::get_head();
	while (cur != NULL) {
		PE* pe = dynamic_cast<PE*>(cur);
		if (pe) {
			output << "1," << pe->get_no() << "," << pe->get_name() << ","
				   << pe->get_run() << "," << pe->get_swim() << "," << pe->get_AI() << endl;
		}
		cur = cur->get_ptr();
	}

	cur = CS::get_head();
	while (cur != NULL) {
		CS* cs = dynamic_cast<CS*>(cur);
		if (cs) {
			output << "2," << cs->get_no() << "," << cs->get_name() << ","
				   << cs->get_prg() << "," << cs->get_ing() << endl;
		}
		cur = cur->get_ptr();
	}

	output.close();
}


// 新增
void add() {
    STNODE* p = NULL;
    int no, major;
    bool valid = false;
    ofstream output("st.dat", ios::app);

    cout << "請輸入學生資料：" << endl;
    cout << "請選擇科系(1：體育系，2：資科系)" << endl;
    cin >> major;

    if (major == 1) {
        p = new PE;
        while (!valid) {
            cout << "座號：";
            cin >> no;
            cin.ignore();

            STNODE* temp = PE::get_head();
            valid = true;
            while (temp != NULL) {
                if (temp->get_no() == no) {
                    cout << "錯誤：座號已經存在，請重新輸入！" << endl;
                    valid = false;
                    break;
                }
                temp = temp->get_ptr();
            }
        }

        p->set_no(no);

        cout << "姓名：";
        string name;
        getline(cin, name);
        p->set_name(name);

        int r, s, a;
        cout << "跑步成績："; cin >> r; 
        cout << "游泳成績："; cin >> s; 
        cout << "AI成績："; cin >> a; 

        dynamic_cast<PE*>(p)->set_run(r);
        dynamic_cast<PE*>(p)->set_swim(s);
        dynamic_cast<PE*>(p)->set_AI(a);
        
        if (output.is_open()) {
            output << "1," << no << "," << name << ","
                   << r << "," << s << "," << a << endl;
        }
        
    } else if (major == 2) {
        p = new CS;
        while (!valid) {
            cout << "座號：";
            cin >> no;
            cin.ignore();

            STNODE* temp = CS::get_head();
            valid = true;
            while (temp != NULL) {
                if (temp->get_no() == no) {
                    cout << "錯誤：座號已經存在，請重新輸入！" << endl;
                    valid = false;
                    break;
                }
                temp = temp->get_ptr();
            }
        }

        p->set_no(no);

        cout << "姓名：";
        string name;
        getline(cin, name);
        p->set_name(name);

        int prg, ing;
        cout << "程式成績："; cin >> prg; 
        cout << "英文成績："; cin >> ing;

        dynamic_cast<CS*>(p)->set_prg(prg);
        dynamic_cast<CS*>(p)->set_ing(ing);
        
        if (output.is_open()) {
            output << "2," << no << "," << name << ","
       		<< prg << "," << ing << endl;
        }

    } else {
        cout << "查無此系！" << endl;
        return;
    }
	
    // 插入新節點
	STNODE* head = (major == 1) ? PE::get_head() : CS::get_head();
	if (head == NULL || head->get_no() > no) {
	    p->set_ptr(head);
	    if (major == 1)
	        PE::set_head(p);  
	    else
	        CS::set_head(p); 
	} else {
	    STNODE* prev = head;
	    STNODE* curr = head->get_ptr();
	    while (curr != NULL && curr->get_no() < no) {
	        prev = curr;
	        curr = curr->get_ptr();
	    }
	    prev->set_ptr(p);
	    p->set_ptr(curr);
	}

    cout << "已新增完畢！" << endl;
     output.close();
}

// 查詢
void search() {
    cout << "請選擇科系(1：體育系，2：資科系)" << endl;
    int major;
    cin >> major;
    
    if (major != 1 && major != 2) {
        cout << "查無此科系！" << endl;
        return;
    }

    cout << "輸入要查詢的學生姓名：";
    bool check = false;
    string name;
    cin.ignore();  
    getline(cin, name);

    STNODE* p = (major == 1) ? PE::get_head() : CS::get_head();

    while (p != NULL) {
        if (p->get_name() == name) {
            cout << "座號: " << p->get_no() << endl;
            cout << "姓名: " << p->get_name() << endl;

            if (major == 1) { // 體育系
                PE* peStudent = dynamic_cast<PE*>(p);
                if (peStudent) {
                    cout << "跑步成績: " << peStudent->get_run() << endl;
                    cout << "游泳成績: " << peStudent->get_swim() << endl;
                    cout << "AI成績: " << peStudent->get_AI() << endl;
                }
            } else if (major == 2) { // 資科系
                CS* csStudent = dynamic_cast<CS*>(p);
                if (csStudent) {
                    cout << "程式成績: " << csStudent->get_prg() << endl;
                    cout << "英文成績: " << csStudent->get_ing() << endl;
                }
            }
            check = true;
            break;
        }
        p = p->get_ptr();  // 移到下一個節點
    }

    if (!check) {
        cout << "該學生不存在" << endl;
    }
}

// 修改
void modify() {
	cout << "請選擇科系(1：體育系，2：資科系)" << endl;
    int major;
    cin >> major;
    
    if (major != 1 && major != 2) {
        cout << "查無此科系！" << endl;
        return;
    }
    
    cout << "輸入要修改的學生座號：";
    int no;
    cin >> no;

    STNODE* p = (major == 1) ? PE::get_head() : CS::get_head();
    while (p != NULL) {
        if (p->get_no() == no) {
            int x = 5;

            if (major == 1) {
                // 體育系
                PE* peStudent = dynamic_cast<PE*>(p);
                if (peStudent) {
                    peStudent->set_run(peStudent->get_run() + x);
                    peStudent->set_swim(peStudent->get_swim() + x);
                    peStudent->set_AI(peStudent->get_AI() + x);
                    cout << "跑步成績已更新為：" << peStudent->get_run() << endl;
                    cout << "游泳成績已更新為：" << peStudent->get_swim() << endl;
                    cout << "AI成績已更新為：" << peStudent->get_AI() << endl;
                } else {
                    cout << "查無此座號！" << endl;
                }
            } else {
                // 資科系：
                CS* csStudent = dynamic_cast<CS*>(p);
                if (csStudent) {
                    *csStudent + x;
                    cout << "程式成績已更新為：" << csStudent->get_prg() << endl;
                    cout << "英文成績已更新為：" << csStudent->get_ing() << endl;
                } else {
                    cout << "查無此座號！" << endl;
                }
            }
            cout << "已更改！" << endl;
            
            save_all();
            return;
        }
        p = p->get_ptr();
    }

    cout << "查無此學生！" << endl;
}

// 刪除
void remove() {
    cout << "請選擇科系(1：體育系，2：資科系)" << endl;
    int major;
    cin >> major;

    if (major != 1 && major != 2) {
        cout << "查無此科系！" << endl;
        return;
    }

    cout << "輸入要刪除的學生座號：";
    int no;
    cin >> no;

    // 根據科系選擇對應的 head
    STNODE* p = (major == 1) ? PE::get_head() : CS::get_head();
    STNODE* prev = NULL;

    while (p != NULL) {
        if (p->get_no() == no) {
            if (prev == NULL) {
                
                if (major == 1) {
                    PE::set_head(p->get_ptr());
                } else {
                    CS::set_head(p->get_ptr());
                }
            } else {
                prev->set_ptr(p->get_ptr());
            }
            delete p;
            cout << "該筆資料已成功刪除！" << endl;
            
            save_all();
            return;
        }
        prev = p;
        p = p->get_ptr();
    }

    cout << "該筆資料不存在，無法刪除！" << endl;
}

// 列印
void print() {
	cout << "請選擇科系(1：體育系，2：資科系)" << endl;
    int major;
    cin >> major;
    
    if (major != 1 && major != 2) {
        cout << "查無此科系！" << endl;
        return;
    }
    
    STNODE* p = (major == 1) ? PE::get_head() : CS::get_head();
    
	cout << "head->";
    while (p != NULL) {
        cout << p->get_no();
        cout << "->";
        p = p->get_ptr();
    }
    cout << "||";
    cout << "已列印！" << endl;
}

// 成績
void score() {
	
	ifstream input("st.dat");
	if (!input) {
	        cout << "無法開啟檔案 st.dat！" << endl;
	        return;
	    }

    cout << "請選擇科系(1：體育系，2：資科系)" << endl;
    int major;
    cin >> major;

    if (major != 1 && major != 2) {
        cout << "查無此科系！" << endl;
        return;
    }

    STNODE* original = (major == 1) ? PE::get_head() : CS::get_head();
    if (original == NULL) {
        cout << "目前沒有任何學生資料。" << endl;
        return;
    }

    // 用複製方式建立排序用串列
    STNODE* sorted = NULL;

    int type, no, r1, r2, r3;
    string name;

	// 從檔案讀取每位學生資料
	string line;
    while (getline(input, line)) {
    	stringstream ss(line);
	    string type_str, no_str, name;
	    string r1_str, r2_str, r3_str;
	
	    getline(ss, type_str, ',');
	    getline(ss, no_str, ',');
	    getline(ss, name, ',');
	
	    int type = atoi(type_str.c_str());
	    int no = atoi(no_str.c_str());

    	STNODE* copy = NULL;

    if (type == 1) { // 體育系：3個成績
        getline(ss, r1_str, ',');
        getline(ss, r2_str, ',');
        getline(ss, r3_str, ',');
        if (major != 1) continue;
        copy = new PE(no, name, atoi(r1_str.c_str()), atoi(r2_str.c_str()), atoi(r3_str.c_str()));
    } else if (type == 2) { // 資科系：2個成績
        getline(ss, r1_str, ',');
        getline(ss, r2_str, ',');
        if (major != 2) continue;
        copy = new CS(no, name, atoi(r1_str.c_str()), atoi(r2_str.c_str()));
    } else {
        continue; // 不認得的 type，跳過
    }

        // 插入排序（由大到小）
        if (sorted == NULL || copy->get_total() > sorted->get_total()) {
            copy->set_ptr(sorted);
            sorted = copy;
        } else {
            STNODE* p = sorted;
            while (p->get_ptr() != NULL && p->get_ptr()->get_total() >= copy->get_total()) {
                p = p->get_ptr();
            }
            copy->set_ptr(p->get_ptr());
            p->set_ptr(copy);
        }
    }

    // 印出標題列
    cout << left
         << setw(8)  << "座號"
         << setw(10) << "姓名";
    if (major == 1) {
        cout << setw(12) << "跑步成績"
             << setw(12) << "游泳成績"
             << setw(12) << "AI成績";
    } else {
        cout << setw(12) << "程式成績"
             << setw(12) << "英文成績";
    }
    cout << "排名" << endl;

    // 印出排序後的結果
    STNODE* p = sorted;
    int rank = 1;
    int prev_total = -1;
    int prev_rank = 1;

    while (p != NULL) {
        // 印出基本資料
        cout << setw(8)  << p->get_no()
             << setw(10) << p->get_name();

        if (major == 1) {
            PE* pe = static_cast<PE*>(p);
            cout << setw(12) << pe->get_run()
                 << setw(12) << pe->get_swim()
                 << setw(12) << pe->get_AI();
        } else {
            CS* cs = static_cast<CS*>(p);
            cout << setw(12) << cs->get_prg()
                 << setw(12) << cs->get_ing();
        }

        // 判斷排名是否相同
        if (p->get_total() != prev_total) {
            cout << rank << endl;
            prev_total = p->get_total();
            prev_rank = rank;
        } else {
            cout << prev_rank << endl;
        }

        STNODE* to_delete = p;
        p = p->get_ptr();
        delete to_delete;
        rank++;
    }

    cout << "已列印學生成績單！" << endl;
    input.close();
}

int main() {
	int major, no, r1, r2, r3;
    string name;
    ifstream input("st.dat");
    string line;
    

    // 從檔案讀取每位學生資料
    while (getline(input, line)) {
    	stringstream ss(line);
	    string type_str, no_str, name;
	    string r1_str, r2_str, r3_str;
	    STNODE* p;
	
	    getline(ss, type_str, ',');
	    getline(ss, no_str, ',');
	    getline(ss, name, ',');
	
	

	    int major = atoi(type_str.c_str());
	    int no = atoi(no_str.c_str());

        if (major == 1) { // 體育系：3個成績
            getline(ss, r1_str, ',');
            getline(ss, r2_str, ',');
            getline(ss, r3_str, ',');
            p = new PE(no, name, atoi(r1_str.c_str()), atoi(r2_str.c_str()), atoi(r3_str.c_str()));
        } else if (major == 2) { // 資科系：2個成績
            getline(ss, r1_str, ',');
            getline(ss, r2_str, ',');
            p = new CS(no, name, atoi(r1_str.c_str()), atoi(r2_str.c_str()));
        } 
        
        // 插入新節點
		STNODE* head = (major == 1) ? PE::get_head() : CS::get_head();
		if (head == NULL || head->get_no() > no) {
		    p->set_ptr(head);
		    if (major == 1)
		        PE::set_head(p);  
		    else
		        CS::set_head(p); 
		} else {
		    STNODE* prev = head;
		    STNODE* curr = head->get_ptr();
		    while (curr != NULL && curr->get_no() < no) {
		        prev = curr;
		        curr = curr->get_ptr();
		    }
		    prev->set_ptr(p);
		    p->set_ptr(curr);
		}
    }

    input.close();
    
    MENU menu;

    do {
        int s;
        menu.show();
        cin >> s;
        menu.w_select(s);
        switch (menu.r_select()) {
        case 0: {
            cout << "已退出" << endl;
            break;
        }
        case 1: {
            add();
            break;
        }
        case 2: {
            search();
            break;
        }
        case 3: {
            remove();
            break;
        }
        case 4: {
            modify();
            break;
        }
        case 5: {
            print();
            break;
        }
        case 6: {
            score();
            break;
        }
        default:
            cout << "無效選項，請重新輸入！" << endl;
        }
        
    } while (menu.r_select() != 0);
    
    

    return 0;
}


