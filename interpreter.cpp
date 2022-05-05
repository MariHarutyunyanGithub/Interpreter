/*
 * Չի կարելի ազատ տող թողնել
 * token-ների միջև առնվազն մեկ բացատ պետք է լինի
 * թույլատրվում է մուտքագրել միայն ամբողջ թվեր
 * մանցորդով բաժանել չի կարելի
 * ամեն ինստրուկցիայի վերջում դրվում է ՛։՛նշանը
 * string literal-ները գրվում են միայն " այսպիսի" չակերտների մեջ
 * լեզուն support է անում խիստ սահմանափակ քանակի սիմվոլներ
 	+,-,*,/,<,>, $(հավասարման պայմանի համար),%(անհավասարման համար),&(logic and),|(logic or)
 * փոփոխականների անունների մեջ արգելվում է ՛―՛ սիմվոլի գործածումը
 * ամեն տողում կարելի է գրել միայն մեկ մաթեմատիկական կամ տրամաբանական գործողություն
 * մաթեմատիկական արտահայտություններում փակագծեր չկան
 * այլ տարօրինակ սիմվոլներ կամ կետադրական նշաններ օգտագործել չի թույլատրվում
 * եթե string ենք տպում, պիտի լինի չակերտների մեջ
 * թիվ կամ փոփոխականի արժեք տպելիս օգտագործում ենք փակագծեր
 
 * */

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

bool is_letter(char);
bool is_number(char);
bool is_number_string(std::string);
bool is_type(std::string);
bool is_my_var_name(std::string);
bool is_new_var_name(std::string);
bool is_loop_keyword(std::string);
bool is_statement_keyword(std::string);
bool is_output(std::string);
bool bool_implementation(std::string, int);
bool do_bool_operation(std::string, std::string, char, int);
int do_math_operation(std::string, int);
int to_correct_operand_type(std::string);
int oper(std::string, std::string,std::string);
int evaluate_as_expression(std::string, int);
int evaluate_as_number_literal(std::string);//stoi
std::string text_analizer(std::string, int);
std::string get_current_token(std::string&);
std::string bool_to_string(bool);
std::string int_to_string(int);
void delete_spaces_and_new_lines(std::string&);
void line_analize(std::string, int);
void definition(std::string, int);
void statement_implementation(std::string, int);
void loop_implementation(std::string, int);
void initialization(std::string, std::string&, int);
void output_implementation(std::string, int);
void error(int);

struct variable{
	std::string var_name;
        std::string var_type;
        std::string var_value;
} my_var;

std::vector<variable> vars_vector;//popoxakannery pahelu hamar
std::vector<std::string> lines;//cody tox ar tox pahelu hamar
std::vector<char> bool_oper = {'$','%','>', '<','&', '|'};
std::vector<std::string> math_oper = {"+", "-", "*", "/"};



bool is_letter(char let){//stugum e` tvyal simvoly tar e, te voch
        bool is_let{false};
        if (let >= 'a' && let <= 'z'){
                is_let = true;
        }else if (let >= 'A' && let <= 'Z'){
                is_let = true;
                }else if (let == '_'){
                        is_let = true;}
        return is_let;
}

bool is_number(char num){//stugum e` tvyal simvoly tiv e, te voch
        bool is_num{false};
        if (num >= '0' && num <= '9'){
                is_num = true;
        }
        return is_num;
}

bool is_number_string(std::string str){//stugum e` tvyal stringy tiv e, te voch
	for (int i = 1; i < str.size(); ++i){
		if (!is_number(str[i])){//ete voreve simvol tiv che
			return false;
		}
	}
	if (is_number(str[0]) || str[0] == '-'){//ete bolory tver en, stugum enq arajin simvoly
		return true;
	}
	return false;
}
void delate_spaces_and_newlines(std::string& str){
	if(str[0] == '\n'){ str.erase(0, 1);}
		for (int i = 0; i <= str.length(); ++i){
			if((str[i] == ' ') && (str[i + 1] == ' ')){
				str.erase (i, 1);
				i--;
			}
		}
}

std::string get_current_token(std::string &str){//stanum e tox,toxic jnjum ev veradarcnum e arajin tokeny
	std::string first_token = "";
        for (int i = 0; i < str.length(); ++i){
        	if (str[i] != ' '){
			first_token += str[i];
		}else{
			str.erase(0,i + 1);
			return first_token;			
		}       
	}
       	return first_token;
}

		
bool is_type(std::string str){
	if(str == "num" || str == "bool" || str == "text" ){
		return true;
	}
	return false;
}

bool is_my_var_name(std::string str){
	if (!is_letter(str[0])){
	 exit(0);
	}
	for (int i= 0; i < vars_vector.size(); ++i){
		if (str == vars_vector[i].var_name){
			return true;
		}
	}
	return false;
}

bool is_new_var_name(std::string str){
	if (!is_letter(str[0])){
		exit(0);
	}
	for (int i = 0; i < vars_vector.size(); ++i){
		if (str == vars_vector[i].var_name){
			return false;
		}
	}
	return true;
}

bool is_loop_keyword(std::string str){
	if (str == "while"){return true;}
	return false;
}

bool is_statement_keyword(std::string str){
	if (str == "if"){return true;}
	return false;
}

bool is_output(std::string str){
	if (str == "print"){return true;}
	return false;
}

int evaluate_as_number_literal(std::string str){//tveri stringy darcnum e int
	int res = 0;
	int res_ = 0;
	if (str[0] != '-'){//ete tivy bacasakan che
        	for (int i = 0; i < str.length(); ++i){
                	res = str[i] - '0' + res * 10;//hashvel tvayin arjeqy
        	}
       	}else{//ete bacasakan e
		for (int i = 1; i < str.length(); ++i){
			res_ = str[i] - '0' + res * 10;//hashvel drakan arjeqy
		}
		res = (-1) * res;//darcnel bacasakan
	}
        return res;
	
}

int to_correct_operand_type(std::string num){
	bool is_number1 = true;
        int int_num1;
        for (int i = 1; i < num.size(); ++i){//nayum e bolor simvolnery` sksac erkrordic
                if (!is_number(num[i])){//ete goyutyun uni gone mek simvol, vory tiv chi
                        is_number1 = false;//is_number-y darcnum enq false
                }
        }
        if (is_number1 && (num[0] == '-' || is_number(num[0]))){//ete bolory tver en, isk arajin simvoly '-' nshann e kam eli tiv e
                int_num1 = evaluate_as_number_literal(num);//int_num1-i mej pahum enq num-i tvayin arjeqy
        }else{//hakarak depqum
                for (int i = 0; i < vars_vector.size(); ++i){//ayn handisanum e popoxakani anun
                        if (num == vars_vector[i].var_name){//gtnum enq nran
                                num = vars_vector[i].var_value;//arjeqy gcum enq num-i mej

                        }
                }
                int_num1 = evaluate_as_number_literal(num);//int_num1-i mej pahum enq num-i tvajin arjeqy
        }
	return int_num1;
}


int oper(std::string num1, std::string num2, std::string op){
	int int_num1 = to_correct_operand_type(num1);//stanal operandneri correct type-y
	int int_num2 = to_correct_operand_type(num2);
	if (op == "+"){
		return int_num1 + int_num2;
	}
	if (op == "-"){
                return int_num1 - int_num2;
        }
	if (op == "*"){
                return int_num1 * int_num2;
        }
	if (op == "/"){
                return int_num1 / int_num2;
        }
	std::cout << "error" << std::endl;
	exit(0);
}


int do_math_operation(std::string str, int line_index){//vercnum e correct argumentnerov artahaytutyunn u indexy,katarum e hamapatasxan gorcoxutyunnery, veradarcnum e int tipi arjeqy
	int result = 0;
	std::string var_val = "";
	std::string first_token = get_current_token(str);//vercnenq arajin tokeny
	for (int i = 0; i < vars_vector.size(); ++i){
		if (first_token == vars_vector[i].var_name){//ete ayn popoxakani anun e
			var_val = vars_vector[i].var_value;//stanum enq nra arjeqy
		}
	}
	if (is_number(first_token[0]) || first_token[0] == '-'){//ete arajin simvoly tiv e kam "-" nshan
		var_val = first_token; // vercnum enq henc ir arjeqy
	}
	std::string second_token = get_current_token(str);//vercnum enq hajord tokeny
	if(second_token == "+" || second_token == "-" || second_token == "*" || second_token == "/"){//yst ajd tokeni uxarkum enq oper funkciayin
		result = oper(var_val,str,second_token);
	}else{error(line_index);}
	return result;	
}

int evaluate_as_expression(std::string str, int line_index){//evaluate enq anum vorpes matematikakan artahaytutyun
	std::string str_copy = str;//str-i arjeqy pahenq anpopox
	int result = 0;
	if (is_number(str[0]) || str[0] == '-'){//ete arajin simvoly tiv e
		std::string first_token = get_current_token(str);//vercnum enq artahaytutyan arajin tokeny 
		for (int i = 1; i < first_token.size(); ++i){
			if(!is_number(first_token[i])){//ete voch bolorn en tvanshanner
				error(line_index);}
		}
		result = do_math_operation(str_copy, line_index);//ete if-i paymany true chdarcav, naxnakan toxy poxancel _do_math_operation funkciayin
	}else if (is_letter(str[0])){//ete arajin simvoly tar e
		std::string first_token = get_current_token(str);//vercnum enq toxi arajin tokeny
		bool is_var = false;
		for (int i = 0; i < vars_vector.size(); ++i){
			if (first_token == vars_vector[i].var_name){//ete ayn popoxakani anun e
				result = do_math_operation(str_copy, line_index);//toxy naxnakan tesqov poxancel do_math_operation funkciayin
				is_var = true;
			}
		}
		if (!is_var){
			error(line_index);}
	}else{
			error(line_index);}
		return result;//veradarcnum enq do_math_operation-i ardyunqy
}

void definition(std::string str, int line_index){//irakanacnum e popoxakani haytararutyun
	std::string second_token = get_current_token(str);//vercnum enq hajord tokeny
        if (is_new_var_name(second_token)){//ete nor popoxakani anun e
		my_var.var_name = second_token;//erkrord tokeny gcum enq variable tipi objekti var_name-i mej
		std::string third_token = get_current_token(str);//vercnum enq hajod tokeny
		if (third_token == "="){
			my_var.var_value = str;//veragrman nshanic heto inch tesnum enq, gcum enq var_value-i mej
			vars_vector.push_back(my_var);//popxakanneri vektori mej gcum enq variable tipi my_var objekty` ir arjeqnerov
			}else{error(line_index);}
	}else{error(line_index);}
}
void output_implementation(std::string str,int line_index){
	std::string second_token = get_current_token(str);//vercnum enq toxi erkrord tokeny
	std::string next_token;
	if (second_token == "->"){//ete amen inch chisht e
		next_token = get_current_token(str);//vercnum enq hajord tokeny
		if (next_token == "("){//ete pakagic e,stugum enq` ardyoq ka erkrordy
			if ( str[str.size() - 2] == ')'){//ete verjin simvoly pakagic e
				std::string print_str = "";
				for (int i = 0; i < str.size() - 2; ++i){
					print_str += str[i];//pakagceri amboxj parunakutyuny gcum enq print_str-i mej
				}
				bool find = false;
				for (int i = 0; i < vars_vector.size(); ++i){
						if (print_str == vars_vector[i].var_name){//ete parunakutyuny popxakani anun e
							std::cout << vars_vector[i].var_value;//tpum enq popoxakani arjeqy
							find = true;
							break;
						}
				}
				if(!find){		
				int  expression_value = evaluate_as_expression(print_str, line_index);//parunakutyunn uxarkum enq hamapatasxan funkciayin, vorn el arjeqy gtnum, veradarcnum e
								std::cout << expression_value;
						}
					}              		
		}else if (next_token == ("\"")){
			std::string print_str = "";
				if (str[str.length() -2] == ('\"')){//ete chakertneri mej e arnvac
					for (int i = 0; i < str.size() - 2; ++i){
						print_str += str[i];
					}
					std::cout << print_str;//nuynutyamb tpel chakertneri parunakutyuny
				}else{error(line_index);}
		}else{error(line_index);}
        }else{error(line_index);}
}
/*

void loop_implementation(std::string str, int line_index){
	statement_implementation(str,line_index);

}
*/
bool do_bool_operation(std::string left, std::string right, char oper, int line_index){//katarum e boolyan gorcoxutyunnery
	int left_int{};
	int right_int{};
	if (is_number_string(left)){//ete dzax operandy tiv e
		left_int = evaluate_as_number_literal(left);//stanum enq nra int arjeqy
	}else if (is_my_var_name(left)){//isk ete popoxakani anun e
		for (int i = 0;i < vars_vector.size(); ++i){
			if (left == vars_vector[i].var_name){//gtnum enq nran
				left = vars_vector[i].var_value;//anvan poxaren dnum enq popoxakani arjeqy
				if ( is_number_string(left)){//ete ayn arden tiv e
					left_int = evaluate_as_number_literal(left);//stanum enq nra int arjeqy
				}
			}
		}
	}else{//ete artahaytutyun e
		left_int = do_math_operation(left, line_index);
	}
	 if (is_number_string(right)){//ete aj operandy tiv e
                right_int = evaluate_as_number_literal(right);//stanum enq nra int arjeqy
        }else if (is_my_var_name(right)){//isk ete popoxakani anun e
                for (int i = 0;i < vars_vector.size(); ++i){
                        if (right == vars_vector[i].var_name){//gtnum enq nran
                                right = vars_vector[i].var_value;//anvan poxaren dnum enq popoxakani arjeqy
                                if ( is_number_string(right)){//ete ayn arden tiv e
                                        left_int = evaluate_as_number_literal(right);//stanum enq nra int arjeqy
                                }
                        }
                }
        }else{//ete artahaytutyun e
                right_int = do_math_operation(right, line_index);
        }
	if (oper == '>'){
		return bool(left_int > right_int);
	}
	if (oper == '<'){
		return bool(left_int < right_int);
	}
	if (oper == '$'){
                return bool(left_int == right_int);
        }
	if (oper == '%'){
                return bool(left_int != right_int);
        }
	if (oper == '&'){
                return bool(left_int && right_int);
        }
	if (oper == '|'){
                return bool(left_int || right_int);
        }
	return false;
}


bool bool_implementation(std::string str, int line_index){//stanum e artahaytutyan boolyan arjeqy
	bool find = false;
	std::string left_operand = "";
	std::string right_operand = "";
	char oper;
	bool value = false;
	int oper_index{};
	int str_index{};
	for (int i = 0; i < str.size(); ++i){
		for (int j = 0; j < bool_oper.size(); ++j){//minchev hamematutyan simvoly gtnely
			if (str[i] == bool_oper[j]){
				find = true;
				oper_index = j;
		                str_index = i;
				break;
			}
		}		
		if (!find){
			left_operand += str[i];//pahel left_operandi mej
		}		
	}
	if(find){//ete gtnvec bool_gorcoxutyan nshan
		oper = bool_oper[oper_index];//operatory fiqsel
		right_operand = str.erase(0,str_index + 1);//mnacacn el pahel right_operandi mej
		value = do_bool_operation(left_operand, right_operand, oper, line_index);//katarel gorcoxutyunn u pahel value-i mej
	}else{//ete bool gorcoxutyun chka toxi mej
		do{//katarel, qani der tiv chenq stacel
			if (is_number_string(str)){//stugel` tiv e, te voch
				value =(bool)evaluate_as_number_literal(str);//stanal int arjeqy, veracel booli
			}else if (is_my_var_name(str)){// hakarak depqum, ete popoxakani anun e
				for (int i = 0; i < vars_vector.size(); ++i){//gtnum enq nra arjeqy
					if (str == vars_vector[i].var_name){
						str = vars_vector[i].var_value;//anuny poxarinum enq arjeqov
					}
				}
			}else{
				error(line_index);
			}
		} while (!is_number_string(str));//gorcoxutyuny krknel aynqan, minchev arjeqy darna tvayin
	}
	std::cout << "line " << line_index << " bool_implementation" << std::endl;
	return value;
}


void statement_implementation(std::string str, int line_index){//paymani irakanacum
	std::string next = get_current_token(str);//vercnum enq arajin tokeny
	std::string first_token;
        int bool_value;
	if (next != "(" || str[str.size() - 2] != ')'){//ete arajin kam verjin tokeny pakagic chi
		error(line_index);//cragirn anjatum enq
	}else{						//hakarak depqum
		bool_value = bool_implementation(str.erase(str.size() - 2), line_index);//pakagceri miji artahaytutyuny poxancum enq hamapatasxan funkciayin, veradarcrac 0 kam 1 arjeqy pahum enq bool_value - i mej
	}
	if (bool_value){//ete pakagceri mijiny true e
		++line_index;//toxi indexn avelacnum enq mekov
		if (get_current_token(str) == "do"){//ete hajord toxy sksvum e "do"-ov
			std::string new_str = "do " + str;//"do"-n verakangnum enq
			line_analize(new_str, line_index);//katarum enq ayd toxy
		}
	}else{//ete pakagceri mijiny false e
			do {
				line_index++;//ancnum enq hajord toxin
				first_token = get_current_token(str);//vercnum enq arajin tokeny
			}while (first_token == "do");//qani der arajin tokeny "do" e
				if (first_token == "else"){//ete arajin tokeny "else" e
					while (get_current_token(str) == "do"){
						std::string new_str = "do " + str;//"do"-n verakangnum enq
                        			line_analize(new_str, line_index);//katarum enq ayd toxy
						++line_index;
					}
				}
	}
	std::cout << "line: " << line_index << " statement_implementation" << std::endl;
}
             		

void error(int line_index){//hamapatasxan haxordagrutyamb cragirn anjatum e
	std::cout << "error in line: " << line_index << std::endl;
	exit(0);
}


std::string text_analizer(std::string str, int line_index){
	if (str[0] == '"' && str[str.size() - 1] == '"'){//ete toxn arnvac e chakertneri mej
		str.erase(0,1);
		str.erase(str.size() - 2, 2);//jnjum enq chakertnery
	}else{error(line_index);}
	std::cout << "text_analizer" <<std::endl;

	return str;//veradarcnum enq parunakutyuny
}

std::string bool_to_string(bool val){
	std::string str = "";
	if (val == 0 || val == false){
		str = "false";
	}else if (val == 1 ||val == true){
		str = "true";
	}else{
		std::cout << "error" << std::endl;
	      	exit(0);
	}
	return str;
}

std::string int_to_string(int num){
	std::string str = "";
	std::string res = "";
	while (num != 0){
		char a  = num % 10 + '0';
		str += a;
		num /= 10;
	}
	for (int i = 0; i < str.size(); ++i){
		 res += str[str.size() - 1 - i];
	}
	return res;

}


void initialization(std::string str,std::string& var, int line_index){//katarum enq veragrum
	if (get_current_token(str) == "="){//ete hajordy "=" nshann e
		std::string type = "";
		int value_int{};
		bool value_bool;
		std::string value_text = "";
		for (int i = 0; i < vars_vector.size(); ++i){
			if(var == vars_vector[i].var_name){//popoxakani anunov gtnum enq tipy
				type = vars_vector[i].var_type;
				if (type == "num"){//ete num tipi e
					value_int = do_math_operation(str,line_index);//mat. gorcoxutyan ardyunqy veragrum enq int tipin
					vars_vector[i].var_value = int_to_string(value_int);//popxakani arjeqy berum enq string tipi ev gcum enq vektori strukturayi mej
					std::cout << " num_type" << std::endl;
				}else if (type == "bool"){//ete bool tipi e
					value_bool = bool_implementation(str,line_index);//bool gorcoxutyan ardyunqy veragrum enq bool tipin
					vars_vector[i].var_value = bool_to_string(value_bool);//arjeqy berum enq string tipi ev  gcum enq vektori strukturayi mej
				}else if (type == "text"){//ete text tipi e
					value_text = text_analizer(str, line_index);//arjeqn analiz aneluc heto veragrum enq value_text-in
					vars_vector[i].var_value = value_text;//arjeqy gcum enq vektori strukturayi mej
				}else {error(line_index);}
			}
		
		}

	}else {error(line_index);}
	std::cout << "line: " << line_index << " initialization" << std::endl;
}

		
void line_analize(std::string str, int line_index){//vercnum e hertakan toxy, yst arajin tokeni uxarkum e hamapatasxan funkciayin
	std::string first_token = get_current_token(str);//vercnum enq arajin tokeny

	if (is_type(first_token)){//ete tvyal tokeny handisanum e tipi anun
		my_var.var_type = first_token;//my_var objekti var_type -in talis enq ajd arjeqy
		definition(str, line_index);//katarum enq popoxakani haytararutyun

	}else if (is_my_var_name(first_token)){//hakarak depqum, ete ajn popoxakani anun e
		initialization(str,first_token,line_index);//toxy,popoxakani anunn u toxi indexy poxancum enq initialization funkciayin

	}else if (is_loop_keyword(first_token)){//hakarak depqum, ete arajin tokeny handisanum e loop_keyword
//		loop_implementation(str,line_index);//toxn u indexy poxancum enq hamapatasxan funkciayin

	}else if (is_statement_keyword(first_token)){//hakarak depqum, ete handisanum e statement_keyword
		statement_implementation(str, line_index);//toxn u indexy poxancum enq hamapatasxan funkciayin

	}else if (is_output(first_token)){//hakarak depqum, ete output keywordin e hamynknum
                output_implementation(str,line_index);//toxn u indexy poxancum enq hamapatasxan funkciayin

        }else if (first_token =="do"){//ete arajin tokeny "do" e
		if (get_current_token(str) == "(" && str[str.size() - 2] == ')'){//stugum enq` ete pakagcery chist en
			line_analize(str.erase(str.size()-2),line_index);//aranc pakagceri noric line_analize funkcian enq kanchum
		}else{//hakarak depqum error
			error(line_index);
		}
	}else if (first_token == "else"){//ete arajin tokenn "else" e
		std::string next = get_current_token(str);
		if (next != "do" && next != "if"){//stugum enq hajord tokeny. ete "do" kam "if" che, cragirn anjatum enq
			error(line_index);
		}else if (next == "do"){//ete hajordy "do" e,
				str = "do" + str;//do keywordi het miacnum enq 
				line_analize(str,line_index);//u noric analiz anum
		}else if (next == "if"){//ete hajord tokeny if e
			statement_implementation(str, line_index);//toxn u indeqsy poxancum enq hamapatasxan funkciayin
		}
	}else {
		error(line_index);//mnacac depqerum` error
	}
	std::cout << "line: " << line_index << std::endl;
}

int main (){
        std::cout << "Please, enter the path of file to read the code_text.\n";
        std::string my_code_path = "text.txt";
        //std::cin >> my_code_path;

        std::ifstream fin;
        fin.open(my_code_path);
        if(!fin.is_open()){
                std::cout << "the file " << my_code_path << " is not opened" << std::endl;
        }
        else{
                std::cout << "The file " << my_code_path << " is opened!\n";
                std::string text;//kodi hertakan toxy pahelu hamar
		std::vector<std::string> lines;//cody tox ar tox pahelu hamar
		int i = 0;
                while(!fin.eof()){//qani der file-i verjin chenq hasel
			std::getline(fin, text, ':');//anjatum enq toxern yst ':' simvoli
			delate_spaces_and_newlines(text);//jnjum enq avelord bacatnern u enternery
			lines.push_back(text);//hertakan toxy gcum enq vektori mej
			i++;
		}

		for(int j = 0; j < lines.size(); j++){
			line_analize(lines[j], j);//yuraqanchyur toxn arandzin analiz enq anum
		}


		fin.close();//pakum enq txt file-y
	}
	return 0;
}
