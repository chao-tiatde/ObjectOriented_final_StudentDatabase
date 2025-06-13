#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

class Account {
	Account* ptr;
    string name;
    int ID;
    
public:
    // 建構子
    Account() : ID(0){}
    Account(int ID, string name) : ID(ID), name(name) {}
    virtual ~Account() {}

    // 資料存取函式
    void set_name(string s) { name = s; }
    void set_ID(int n) { ID = n; }
    
    int get_ID() { return ID; }
    string get_name() { return name; }
    
    void set_ptr(Account* p) { ptr = p; }
    Account* get_ptr() { return ptr; }
};

class TW_Account: public Account{
	int rest;
	int total_borrow;

public:
	TW_Account(int ID = 0, string name = "", int rest = 0, int total_borrow = 0): rest(rest), total_borrow(total_borrow), Account(ID, name) {}
	// 運算子重載
    void operator+(int x) { rest += x; }
    void operator-(int y) { rest -= y; }
    void operator+=(int a){total_borrow += a;}
    void operator-=(int b){total_borrow -= b;}
    
    
	void set_rest(int a) { rest = a; }
    void set_total_borrow(int b) { total_borrow = b; }
    
    int get_rest() { return rest; }
    int get_total_borrow() { return total_borrow; }
    
    //int get_total() { return (run + swim + AI); }

};

class JP_Account: public Account{
	int rest;
	int total_borrow;
	
public:
	JP_Account(int ID = 0, string name = "", int rest = 0, int total_borrow = 0): rest(rest), total_borrow(total_borrow), Account(ID, name) {}
	void operator+(int x) { rest += x; }
    void operator-(int y) { rest -= y; }
    void operator+=(int a){total_borrow += a;}
    void operator-=(int b){total_borrow -= b;}
    //void operator+(int x) { prg += x; ing += x; }
	
	void set_rest(int a) { rest = a; }
    void set_total_borrow(int b) { total_borrow = b; }
    int get_rest() { return rest; }
    int get_total_borrow() { return total_borrow; }
    //int get_total() { return (prg + ing); }
    // 靜態資料操作
    
};

class Bank {
    int select;
    double rest_money;
    Account* TW_head;
    Account* JP_head;
public:
	void set_rest_money(double r) { rest_money = r; }
	double get_rest_money() { return rest_money; }
    void operator+(double x) { rest_money += x; }
    void operator-(double x) { rest_money -= x; }
    
    void set_TW_head(Account* p) { TW_head = p; }
    void set_JP_head(Account* p) { JP_head = p; }
    Account* get_TW_head() { return TW_head; }
    Account* get_JP_head() { return JP_head; }
    
    Bank() : select(1), rest_money(0.00), TW_head(NULL), JP_head(NULL) {}

    void w_select(int x) { select = x; }
    int r_select() { return select; }
    void show() {
        cout << "\n選單" << endl;
        cout << "1. 新增帳戶資料" << endl;
        cout << "2. 查詢帳戶資料" << endl;
        cout << "3. 用戶存、取錢" << endl;
        cout << "4. 用戶借、還錢" << endl;
        cout << "5. 顯示銀行餘額" << endl;
        cout << "6. 顯示所有資料至螢幕" << endl;
        cout << "7. 列印所有資料至檔案" << endl;
        cout << "0. 離開" << endl;
        cout << "請輸入選擇項目？";
    }
};

// 新增
void add(Bank& Bank) {
    Account* p = NULL;
    int ID, country;
    bool valid = false;
    ofstream output("output.txt", ios::app);

    cout << "請輸入帳號資料：" << endl;
    cout << "請選擇帳號類型(1：TW，2：JP)" << endl;
    cin >> country;
    cin.ignore();

    if (country == 1) {
        p = new TW_Account;
        ID  = 10001;
        Account *temp = Bank.get_TW_head(); 
        while (!valid) {
            valid = true;
            temp = Bank.get_TW_head();
            while (temp != NULL) {
                if (temp->get_ID() == ID) {
                    //cout << "錯誤：帳號已經存在，請重新輸入！" << endl;
                    ID+=1;
                    valid = false;
                    break;
                }
                temp = temp->get_ptr();
            }
        }

        p->set_ID(ID);

        cout << "姓名：";
        string name;
        getline(cin, name);
        p->set_name(name);
        
        cout << "初始金額：";
        int initial_money;
        cin >> initial_money;
        if(initial_money < 0){
		cout << "不可為負數" << endl;
		return;}
        dynamic_cast<TW_Account*>(p)->set_rest(initial_money);
        Bank + initial_money;
        
        //if (output.is_open()) {
            //output << "1," << no << "," << name << ","
                   //<< r << "," << s << "," << a << endl;
        //}
        
        
    } else if (country == 2) {
        p = new JP_Account;
        ID = 20001;
        Account* temp = Bank.get_JP_head();
        while (!valid) {
            valid = true;
            temp = Bank.get_JP_head();
            while (temp != NULL) {
                if (temp->get_ID() == ID) {
                    ID+=1;
                    valid = false;
                    break;
                }
                temp = temp->get_ptr();
            }
        }

        p->set_ID(ID);

        cout << "姓名：";
        string name;
        getline(cin, name);
        p->set_name(name);
        
        cout << "初始金額：";
        int initial_money;
        cin >> initial_money;
        if(initial_money < 0){
		cout << "不可為負數" << endl;
		return;}
        dynamic_cast<JP_Account*>(p)->set_rest(initial_money);
        Bank + (initial_money*0.2); 
        
        //if (output.is_open()) {
            //output << "2," << no << "," << name << ","
       		//<< prg << "," << ing << endl;
        //}

    } else {
        cout << "無此帳號類型！" << endl;
        return;
    }
	
    // 插入新節點
	Account* head = (country == 1) ? Bank.get_TW_head() : Bank.get_JP_head();
	if (head == NULL || head->get_ID() > ID) {
	    p->set_ptr(head);
	    if (country == 1)
	        Bank.set_TW_head(p);  
	    else
	        Bank.set_JP_head(p); 
	} else {
	    Account* prev = head;
	    Account* curr = head->get_ptr();
	    while (curr != NULL && curr->get_ID() < ID) {
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
void search(Bank& Bank) {

    cout << "輸入要查詢的帳號姓名：";
    bool check_TW = false;
    bool check_JP = false;
    string name;
    cin.ignore();  
    getline(cin, name);

    Account* p = Bank.get_TW_head();

    while (p != NULL) {
        if (p->get_name() == name) {
    
            TW_Account* peStudent = dynamic_cast<TW_Account*>(p);
                if (peStudent) {
                	cout << "ID: " << p->get_ID() << endl;
            		cout << "姓名: " << p->get_name() << endl;
                    cout << "餘額: " << peStudent->get_rest() << endl;
                    cout << "借錢總數: " << peStudent->get_total_borrow() << endl;
                }
                check_TW = true;
        }
        p = p->get_ptr();  // 移到下一個節點
    }
    
    if (!check_TW) {
        cout << "TW Account內無符合資料" << endl;  
    }
    
    p = Bank.get_JP_head();
    while (p != NULL) {
        if (p->get_name() == name) {
    
            JP_Account* peStudent = dynamic_cast<JP_Account*>(p);
                if (peStudent) {
                	cout << "ID: " << p->get_ID() << endl;
            		cout << "姓名: " << p->get_name() << endl;
                    cout << "餘額: " << peStudent->get_rest() << endl;
                    cout << "借錢總數: " << peStudent->get_total_borrow() << endl;
                }
                check_JP = true;
        }
        p = p->get_ptr();  // 移到下一個節點
    }

    if (!check_JP) {
        cout << "JP Account內無符合資料" << endl;  
    }
}

//存取錢 
void SaveTake(Bank& Bank) {
	cout << "輸入使用者ID：" << endl; 
    string ID;
    cin >> ID;
    
    int int_ID = atoi(ID.c_str());

    Account* p = (ID[0] == '1') ? Bank.get_TW_head() : Bank.get_JP_head();
    
    while (p != NULL) {
        if (p->get_ID() == int_ID) {
        	cout << "請選擇存錢或取錢(1: 存錢 2. 取錢)：";
    		int option;
    		cin >> option;
    		
    		cout << "銀行餘額為：" << fixed << setprecision(2) << Bank.get_rest_money() << endl;

        	cout << "請輸入金額："<< endl; 
            int x ;
            cin >> x; 
            if(x < 0){
				cout << "不可為負數" << endl;
				return;}

            if (ID[0] == '1') {
                // TW_Account
                TW_Account* peStudent = dynamic_cast<TW_Account*>(p);
                if (peStudent) {
                	if(option==1){
                		peStudent->set_rest(peStudent->get_rest() + x);
                		Bank + x;
                		cout << "餘額已更新為：" << peStudent->get_rest() << endl;
					}
					if(option==2){
                		//使用者餘額不小於取錢量 
                		if(peStudent->get_rest() < x){
                			cout << "餘額不足！：" << endl; 
                		//銀行剩餘金錢不小於取錢量 
						}else if(Bank.get_rest_money() < x){
						cout << "銀行剩餘金錢不足！" << endl; 
						} else{
						peStudent->set_rest(peStudent->get_rest() - x);
						Bank - x;
						cout << "餘額已更新為：" << peStudent->get_rest() << endl;}
					}
                } 
            } else {
                JP_Account* peStudent = dynamic_cast<JP_Account*>(p);
                if (peStudent) {
                	if(option==1){
                		peStudent->set_rest(peStudent->get_rest() + x);
                		Bank + (x*0.2);
                		cout << "餘額已更新為：" << peStudent->get_rest() << endl;
					}
					if(option==2){
                		//使用者餘額不小於取錢量 
                		if(peStudent->get_rest() < x){
                			cout << "餘額不足！：" << endl; 
                		//銀行剩餘金錢不小於取錢量 
						}else if(Bank.get_rest_money() < (x*0.2)){
						cout << "銀行剩餘金錢不足！" << endl;  
						} else{
						peStudent->set_rest(peStudent->get_rest() - x);
						Bank - (x*0.2);
						cout << "餘額已更新為：" << peStudent->get_rest() << endl;
						}
                	} 
            	}
        	}
        return;
    	}
        p = p->get_ptr();
    }
    cout << "查無此帳號！" << endl;
}

// 借還錢 
void BorrowLent(Bank& Bank) {
	cout << "輸入使用者ID：" << endl; 
    string ID;
    cin >> ID;
    
    int int_ID=atoi(ID.c_str());

    Account* p = (ID[0] == '1') ? Bank.get_TW_head() : Bank.get_JP_head();
    
    while (p != NULL) {
        if (p->get_ID() == int_ID) {
        	cout << "請選擇借錢或還錢(1: 借錢 2. 還錢)：";
    		int option;
    		cin >> option;
    		
    		cout << "銀行餘額為：" << fixed << setprecision(2) << Bank.get_rest_money() << endl;

    		
        	cout << "請輸入金額："<< endl; 
            int x ;
            cin >> x; 
            if(x < 0){
				cout << "不可為負數" << endl;
				return;}

            if (ID[0] == '1') {
                // TW_Account
                TW_Account* peStudent = dynamic_cast<TW_Account*>(p);
                if (peStudent) {
                	if(option==1){
                		if(Bank.get_rest_money() < x){
                			cout << "銀行剩餘金錢不足！" << endl;
						}else{
							peStudent->set_total_borrow(peStudent->get_total_borrow() + x);
							Bank - x;
							cout << "借錢總額已更新為：" << peStudent->get_total_borrow() << endl;
						}
					}
					if(option==2){
						if(x > peStudent->get_total_borrow()){
							cout << "還錢金額大於借錢量！" << endl;
						}else{
							peStudent->set_total_borrow(peStudent->get_total_borrow() - x);
							Bank + x;
							cout << "借錢總額已更新為：" << peStudent->get_total_borrow() << endl;
						}
					}
           	 	}
			 }else {
                JP_Account* peStudent = dynamic_cast<JP_Account*>(p);
                if (peStudent) {
                	if(option==1){
                		if(Bank.get_rest_money() < (x*0.2)){
                			cout << "銀行剩餘金錢不足！" << endl;
						}else{
							peStudent->set_total_borrow(peStudent->get_total_borrow() + x);
							Bank - (x*0.2); 
							cout << "借錢總額已更新為：" << peStudent->get_total_borrow() << endl;
						}
					}
					if(option==2){
						if(x > peStudent->get_total_borrow()){
							cout << "還錢金額大於借錢量！" << endl;
						}else{
							peStudent->set_total_borrow(peStudent->get_total_borrow() - x);
							Bank + (x*0.2);
							cout << "借錢總額已更新為：" << peStudent->get_total_borrow() << endl;
						}
					}
                } 
            }
			return;
        }
        p = p->get_ptr();
    }

    cout << "查無此帳號！" << endl;
}

//銀行餘額
void bankShow(Bank& Bank){
	cout << "銀行餘額為：" << fixed << setprecision(2) << Bank.get_rest_money() << endl;
} 

// 顯示 
void DataShow(Bank& Bank) {
    Account* p = Bank.get_TW_head();
    if (p == NULL) {
        cout << "目前沒有任何TW帳戶資料。" << endl;
    } else {
        // 印出 TW 帳戶資料
        cout << "TW帳戶資料：" << endl;
        cout << left
             << setw(8)  << "ID"
             << setw(10) << "姓名"
             << setw(12) << "餘額"
             << setw(12) << "借錢總額" << endl;

        while (p != NULL) {
            TW_Account* tw = static_cast<TW_Account*>(p);
            cout << setw(8)  << tw->get_ID()
                 << setw(10) << tw->get_name()
                 << setw(12) << tw->get_rest()
                 << setw(12) << tw->get_total_borrow() << endl;
            p = p->get_ptr();
        }
    }

    p = Bank.get_JP_head();
    if (p == NULL) {
        cout << "目前沒有任何JP帳戶資料。" << endl;
    } else {
        // 印出 JP 帳戶資料
        cout << "JP帳戶資料：" << endl;
        cout << left
             << setw(8)  << "ID"
             << setw(10) << "姓名"
             << setw(12) << "餘額"
             << setw(12) << "借錢總額" << endl;

        while (p != NULL) {
            JP_Account* jp = static_cast<JP_Account*>(p);
            cout << setw(8)  << jp->get_ID()
                 << setw(10) << jp->get_name()
                 << setw(12) << jp->get_rest()
                 << setw(12) << jp->get_total_borrow() << endl;
            p = p->get_ptr();
        }
    }

    // 統一結尾訊息
    cout << "已顯示！" << endl;
}


void print(Bank& Bank) {
	ofstream fout("output.txt");  // 新增輸出檔案
    if (!fout) {
        cout << "無法開啟檔案 output.txt！" << endl;
        return;
    }
    
    Account* p = Bank.get_TW_head();
    if (p == NULL) {
        fout << "目前沒有任何TW帳戶資料。" << endl;
        cout << "目前沒有任何TW帳戶資料。" << endl;
    }else{
	// 印出標題列
	cout << "TW帳戶資料：" << endl;
	fout << "TW帳戶資料：" << endl;
	cout << left
         << setw(8)  << "ID"
         << setw(10) << "姓名"
         << setw(12) << "餘額"
         << setw(12) << "借錢總額" << endl;
	
    fout << left
         << setw(8)  << "ID"
         << setw(10) << "姓名"
         << setw(12) << "餘額"
         << setw(12) << "借錢總額" << endl;
      
    while (p != NULL) {
        // 印出基本資料
        TW_Account* tw = static_cast<TW_Account*>(p);
        cout << setw(8)  << tw->get_ID()
             << setw(10) << tw->get_name()
             << setw(12) << tw->get_rest()
             << setw(12) << tw->get_total_borrow() << endl;
        
        fout << setw(8)  << tw->get_ID()
             << setw(10) << tw->get_name()
             << setw(12) << tw->get_rest()
             << setw(12) << tw->get_total_borrow() << endl;
             p = p->get_ptr();
    }	
	}
    p = Bank.get_JP_head();
    if (p == NULL) {
    	cout << "目前沒有任何JP帳戶資料。" << endl;
        fout << "目前沒有任何JP帳戶資料。" << endl;
    }else{
    	cout << "JP帳戶資料：" << endl;
		fout << "JP帳戶資料：" << endl;
    	cout << left
         << setw(8)  << "ID"
         << setw(10) << "姓名"
         << setw(12) << "餘額"
         << setw(12) << "借錢總額" << endl;
    	
    	fout << left
         << setw(8)  << "ID"
         << setw(10) << "姓名"
         << setw(12) << "餘額"
         << setw(12) << "借錢總額" << endl;
		      
    while (p != NULL) {
        // 印出基本資料
        JP_Account* jp = static_cast<JP_Account*>(p);
        cout << setw(8)  << jp->get_ID()
             << setw(10) << jp->get_name()
             << setw(12) << jp->get_rest()
             << setw(12) << jp->get_total_borrow() << endl;
        
        fout << setw(8)  << jp->get_ID()
             << setw(10) << jp->get_name()
             << setw(12) << jp->get_rest()
             << setw(12) << jp->get_total_borrow() << endl;
             p = p->get_ptr();
    }
	}
    fout.close();
    cout << "已列印！" << endl;
    //input.close();
}

//存資料 
void save(Bank& bank) {
    ofstream fout("data.txt");
    if (!fout) {
        cout << "檔案開啟失敗！" << endl;
        return;
    }
    
    // 存TW帳戶
    Account* p = bank.get_TW_head();
    while (p != NULL) {
        TW_Account* tw = dynamic_cast<TW_Account*>(p);
        if (tw) {
            fout << 1 << "," << tw->get_ID() << "," << tw->get_name() << ","
                 << tw->get_rest() << "," << tw->get_total_borrow() << "\n";
        }
        p = p->get_ptr();
    }
    
    // 存JP帳戶
    p = bank.get_JP_head();
    while (p != NULL) {
        JP_Account* jp = dynamic_cast<JP_Account*>(p);
        if (jp) {
            fout << 2 << "," << jp->get_ID() << "," << jp->get_name() << ","
                 << jp->get_rest() << "," << jp->get_total_borrow() << "\n";
        }
        p = p->get_ptr();
    }
    
    fout.close();
    cout << "資料已存檔至data.txt" << endl;
}

//載入資料
void load(Bank& Bank) {
    ifstream fin("data.txt");
    if (!fin) {
        ofstream fout("data.txt", ios::app);
        return;
    }
    
    Bank.set_TW_head(NULL);
    Bank.set_JP_head(NULL);

    string line;
    while (getline(fin, line)) {
        stringstream ss(line);
        string token;
        
        int type, ID, rest, total_borrow;
        string name;
        
        // 讀取帳戶類型
        getline(ss, token, ',');
        type = atoi(token.c_str());

        // 讀ID
        getline(ss, token, ',');
        ID = atoi(token.c_str());

        // 讀姓名
        getline(ss, name, ',');

        // 讀餘額
        getline(ss, token, ',');
        rest = atoi(token.c_str());

        // 讀借款總額
        getline(ss, token, ',');
        total_borrow = atoi(token.c_str());

        Account* p = NULL;
        if (type == 1) {
            p = new TW_Account(ID, name, rest, total_borrow);
            // 插入TW串列(由小到大ID)
            Account* head = Bank.get_TW_head();
            if (head == NULL || head->get_ID() > ID) {
                p->set_ptr(head);
                Bank.set_TW_head(p);
            } else {
                Account* prev = head;
                Account* curr = head->get_ptr();
                while (curr != NULL && curr->get_ID() < ID) {
                    prev = curr;
                    curr = curr->get_ptr();
                }
                prev->set_ptr(p);
                p->set_ptr(curr);
            }
        } else if (type == 2) {
            p = new JP_Account(ID, name, rest, total_borrow);
            // 插入JP串列(由小到大ID)
            Account* head = Bank.get_JP_head();
            if (head == NULL || head->get_ID() > ID) {
                p->set_ptr(head);
                Bank.set_JP_head(p);
            } else {
                Account* prev = head;
                Account* curr = head->get_ptr();
                while (curr != NULL && curr->get_ID() < ID) {
                    prev = curr;
                    curr = curr->get_ptr();
                }
                prev->set_ptr(p);
                p->set_ptr(curr);
            }
        }
    }
    
    fin.close();
    cout << "資料已從data.txt載入" << endl;
}

int main() {
	Bank menu;
	
    load(menu);
    string line;

    do {
        int s;
        menu.show();
        cin >> s;
        menu.w_select(s);
        switch (menu.r_select()) {
        case 0: {
        	save(menu);
            cout << "已退出" << endl;
            break;
        }
        case 1: {
            add(menu);
            break;
        }
        case 2: {
            search(menu);
            break;
        }
        case 3: {
            SaveTake(menu);
            break;
        }
        case 4: {
            BorrowLent(menu);
            break;
        }
		case 5: {
            bankShow(menu);
            break;
        }
        case 6: {
            DataShow(menu);
            break;
        }
        case 7: {
            print(menu);
            break;
        }
        default:
            cout << "無效選項，請重新輸入！" << endl;
        }
        
    } while (menu.r_select() != 0);
    
    

    return 0;
}


