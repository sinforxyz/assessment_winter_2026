#include "rm_a0/a0_lib.hpp"

#include "rm_a0/a0_01_temperature.hpp"
#include "rm_a0/a0_02_leap_year.hpp"
#include "rm_a0/a0_03_range_sum.hpp"
#include "rm_a0/a0_04_vowel_count.hpp"
#include "rm_a0/a0_05_score_stats.hpp"
#include "rm_a0/a0_06_bigint.hpp"
#include "rm_a0/a0_07_log_analyzer.hpp"
#include "rm_a0/a0_08_raii_handle.hpp"

#include <cctype>
#include <cstdio>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>

namespace rm_a0 {

// ==================== A0-01 Temperature ====================
// TODO: 完成下面函数的实现

double CelsiusToFahrenheit(double celsius){
  return celsius*9.0/5.0+32.0;
}

std::string FormatFahrenheit(double fahrenheit){
  char buffer[64];
  snprintf(buffer, sizeof(buffer), "%.2f\n", fahrenheit);
  return std::string(buffer);
}
std::string SolveTemperature(const std::string& input, bool& ok) {
    std::istringstream in(input);
    double celsius = 0.0;
    if (!(in >> celsius)) {
        ok = false;
        return {};
    }

    ok = true;
    return FormatFahrenheit(CelsiusToFahrenheit(celsius));
}

// ==================== A0-02 Leap Year ====================
// TODO: 完成下面函数的实现
bool IsLeapYear(int year){
  if (year % 400 == 0) {
    return true; 
  } else if (year % 100 == 0) {
    return false; 
  } else if (year % 4 == 0) {
    return true; 
  } else {
    return false;
  }
}

std::string FormatLeapYearAnswer(bool is_leap_year){
  std::string ok;
  if(is_leap_year){
    ok="YES\n";
  }else{
    ok="NO\n";
  }
  return ok;
}

// Parses year from input, returns "YES\n" or "NO\n".
// If parsing fails, ok=false and returns empty string.
std::string SolveLeapYear(const std::string& input, bool& ok) {
    std::istringstream in(input);
    int year = 0;
    if (!(in >> year)) {
        ok = false;
        return {};
    }

    ok = true;
    return FormatLeapYearAnswer(IsLeapYear(year));
}


// ==================== A0-03 Range Sum ====================
// TODO: 完成下面函数的实现
long long RangeSum(long long l, long long r) {
    if (l > r) return 0;
    return (l + r) * (r - l + 1) / 2;
}

std::string SolveRangeSum(const std::string& input, bool& ok) {
    std::istringstream in(input);
    long long l = 0;
    long long r = 0;
    if (!(in >> l >> r)) {
        ok = false;
        return {};
    }
    ok = true;
    std::ostringstream out;
    out << RangeSum(l, r) << "\n";
    return out.str();
}

// ==================== A0-04 Vowel Count ====================

namespace {
    namespace a0_04_detail {

        bool IsVowelChar(unsigned char c) {
            // TODO: 完成下面函数的实现
            c=std::tolower(c);
            char vowel[]={'a','e','i','o','u'};
            for(int i=0;i<5;i++){
                if(vowel[i]==c)
                return true;
            }
            return false;
        }

    } // namespace a0_04_detail
} // namespace

std::size_t CountVowels(const std::string& line) {
    std::size_t count = 0;
    // TODO: 完成下面函数的实现
    for(char c:line){
        if(a0_04_detail::IsVowelChar(c))
        count++;
    }
        
    return count;
}

std::string SolveVowelCount(const std::string& input, bool& ok) {
    std::istringstream in(input);
    std::string line;
    if (!std::getline(in, line)) {
        ok = false;
        return {};
    }
    ok = true;
    std::ostringstream out;
    out << CountVowels(line) << "\n";
    return out.str();
}

// ==================== A0-05 Score Stats ====================

ScoreStatsResult ComputeScoreStats(const std::string& input, bool& ok) {
    ok = false;
    std::istringstream in(input);
    // TODO: 完成下面函数的实现

    int n;
    if (!(in >> n) || n <= 0) {
        return ScoreStatsResult{};
    }
    
    ScoreStatsResult result;
    result.top_score = 0;
    int total_score = 0;
    
    for (int i = 0; i < n; i++) {
        std::string name;
        int score;
        
        if (!(in >> name >> score)) {
            return ScoreStatsResult{};
        }
        
        if (score > result.top_score) {
            result.top_score = score;
            result.top_name = name;
        }
        
        total_score += score;
    }
    
    
    
    ok = true;
    
    result.avg = static_cast<double>(total_score) / n;
    return result;
}

std::string SolveScoreStats(const std::string& input, bool& ok) {
    auto res = ComputeScoreStats(input, ok);
    if (!ok) {
        return {};
    }

    std::ostringstream out;
    out << "top=" << res.top_name << " " << res.top_score << "\n";
    out << "avg=" << std::fixed << std::setprecision(2) << res.avg << "\n";
    return out.str();
}

// ==================== A0-06 BigInt ====================

// TODO: 参考hpp完成类实现
/*
at a0_06_bigint.hpp:
class BigInt {
public:
  BigInt();

  // Constructs from a non-negative decimal string.
  explicit BigInt(const std::string &s);

  friend BigInt operator+(const BigInt &a, const BigInt &b);
  friend std::ostream &operator<<(std::ostream &os, const BigInt &x);

private:
  // Little-endian digits, each 0..9.
  std::vector<int> digits_;
};
*/
BigInt::BigInt(){
    digits_.push_back(0);
}
BigInt::BigInt(const std::string &s){
    if (s.empty()) {
        digits_.push_back(0);
        return;
    }
    for (int i = s.length() - 1; i >= 0; i--) {
        char c = s[i];
        if (c<'0'||c>'9') {
            digits_.clear();
            digits_.push_back(0);
            return;
        }
        digits_.push_back(c - '0');
    }
    while (digits_.size() > 1 && digits_.back() == 0) {
        digits_.pop_back();
    }
}
BigInt operator+(const BigInt &a, const BigInt &b){
    BigInt result;
    result.digits_.clear();  
    int carry = 0; 
    int  i = 0;
    
    while (i < a.digits_.size()||i<b.digits_.size() || carry > 0) {
        int digit_a = (i < a.digits_.size()) ? a.digits_[i] : 0;
        int digit_b = (i < b.digits_.size()) ? b.digits_[i] : 0;
        
        int sum = digit_a + digit_b + carry;
        result.digits_.push_back(sum % 10); 
        carry = sum / 10;                     
        
        i++;
    }
    
    return result;

}
std::ostream &operator<<(std::ostream &os, const BigInt &x){
    for(int i=x.digits_.size()-1;i>=0;i--){
        os<<x.digits_[i];
    }
    return os;
}

std::string SolveBigIntAdd(const std::string& input, bool& ok) {
    std::istringstream in(input);
    std::string a;
    std::string b;
    std::ostringstream out;
    if (!std::getline(in, a)) {
        ok = false;
        return {};
    }
    if (!std::getline(in, b)) {
        ok = false;
        return {};
    }
    BigInt A=BigInt(a);
    BigInt B=BigInt(b);
    out<<A+B<<"\n";

    ok = true;
    return out.str();
}

// ==================== A0-07 Log Analyzer ====================
/*
at a0_07_log_analyzer.hpp:
struct LogStats {
  long long info = 0;
  long long warn = 0;
  long long error = 0;
  double avg_ms = 0.0;
  std::string max_level;
  long long max_ms = 0;
};
*/
LogStats AnalyzeLogFile(const std::string& path, bool& ok) {
    ok=false;
    LogStats log;

    std::ifstream file(path);
    if(!file.is_open()){
        return log;
    }
    long long cnt=0;
    std::string line;

    while(std::getline(file,line)){
        std::istringstream lines(line);
        std::string level;
        double ms;
        lines>>level>>ms;
        if(level=="INFO"){
            log.info++;
        }else if(level=="WARN"){
            log.warn++;
        }else if(level=="ERROR"){
            log.error++;
        }
        log.avg_ms+=ms;
        cnt++;
        if(ms>log.max_ms){
            log.max_ms=ms;
            log.max_level=level;
        }

    }

    log.avg_ms/=cnt;
    file.close();
    ok=true;
    return log;
}

std::string SolveLogAnalyzer(const std::string& input, bool& ok) {
    std::istringstream in(input);
    std::string path;
    if (!std::getline(in, path)) {
        ok = false;
        return {};
    }
    if (path.empty()) {
        ok = false;
        return "FAIL\n";
    }

    bool file_ok = false;
    LogStats s   = AnalyzeLogFile(path, file_ok);
    if (!file_ok) {
        ok = false;
        return "FAIL\n";
    }

    ok = true;
    std::ostringstream out;
    out << "INFO=" << s.info << "\n";
    out << "WARN=" << s.warn << "\n";
    out << "ERROR=" << s.error << "\n";
    out << "avg=" << std::fixed << std::setprecision(2) << s.avg_ms << "\n";
    out << "max=" << s.max_level << " " << s.max_ms << "\n";
    return out.str();
}

// ==================== A0-08 RAII Handle ====================

// TODO: 参考hpp完成类实现
/*
at a0_08_raii_handle.hpp:
class FileHandle {
public:
  FileHandle() = default;
  FileHandle(const char *path, const char *mode);
  ~FileHandle();

  FileHandle(const FileHandle &) = delete;
  FileHandle &operator=(const FileHandle &) = delete;

  FileHandle(FileHandle &&other) noexcept;
  FileHandle &operator=(FileHandle &&other) noexcept;

  bool valid() const;
  FILE *get() const;

private:
  FILE *fp_ = nullptr;
};
*/
FileHandle::FileHandle(const char *path,const char *mode){
    if(path&&mode)
    fp_=std::fopen(path,mode);
}
FileHandle::~FileHandle(){
    if(fp_){
        std::fclose(fp_);
    }
}
FileHandle::FileHandle(FileHandle&&other)noexcept:fp_(other.fp_){
    other.fp_=nullptr;
}
FileHandle&FileHandle::operator=(FileHandle&&other)noexcept{
    if(this!=&other){
        if(fp_){
            std::fclose(fp_);
        }
        fp_=other.fp_;
        other.fp_=nullptr;
    }
    return *this;
}
bool FileHandle::valid()const{
    return fp_!=nullptr;
}
FILE*FileHandle::get()const{
    return fp_;
}

bool CopyFile(const std::string& in_path, const std::string& out_path) {
    FileHandle in(in_path.c_str(),"rb");
    if(!in.valid()){
        return false;
    }
    FileHandle out(out_path.c_str(),"wb");
    if(!out.valid()){
        return false;
    }
    const size_t size=4096;
    char buffer[size];
    while(true){
        size_t br=std::fread(buffer,1,size,in.get());
        if(br==0){
            if(std::feof(in.get())){
                break;
            }else{
                return false;
            }
        }

        size_t bw=std::fwrite(buffer,1,br,out.get());
        if(bw!=br){
            return false;
        }
    }
    if(std::fflush(out.get())!=0){
        return false;
    }
    return true;
}

std::string SolveRaiiCopy(const std::string& input, bool& ok) {
    std::istringstream in(input);
    std::string in_path;
    std::string out_path;
    if (!(in >> in_path >> out_path)) {
        ok = false;
        return {};
    }

    if (CopyFile(in_path, out_path)) {
        ok = true;
        return "OK\n";
    }

    ok = false;
    return "FAIL\n";
}

// ==================== A0-09 Text Pipeline====================
//处理器部分
class processors{
  public:
  virtual ~processors(){};
  virtual std::string process(std::string input)=0; 
};
class Trim:public processors{
    public:
    std::string process(std::string input)override{
        std::string result;
        if(input.empty()){
            return "";
        }
        size_t begin=0;
        size_t end=input.size();
        while(begin<end&&std::isspace(static_cast<unsigned char>(input[begin]))){
            begin++;
        }
        while(begin<end&&std::isspace(static_cast<unsigned char>(input[end-1]))){
            end--;
        }
        for(int i=begin;i<end;i++){
            result.push_back(input[i]);
        }
        return result;
    }
};
class Upper:public processors{
    public:
    std::string process(std::string input)override{
        std::string result=input;
        if(input.empty()){
            return "";
        }
        for(char&c:result){
            if(c>='a'&&c<='z'){
                c=c+'A'-'a';
            }
        }
        return result;
    }
};
class Replace:public processors{
    public:
    Replace(std::string from_,std::string to_){
        from=from_;
        to=to_;
    }
    std::string process(std::string input)override{
        std::string result;
        if(input.empty()){
            return "";
        }

        size_t begin=0,found=input.find(from);
        while(found!=std::string::npos){
            result.append(input,begin,found-begin);
            result.append(to);
            begin=found+from.size();
            found=input.find(from,begin);
        }
        result.append(input,begin,input.size()-begin);
        return result;

    }
    private:
    std::string from;
    std::string to;
};
void cleanprocessor(std::vector<processors*>&processor){
    for(auto*one:processor){
        delete one;
    }
    processor.clear();
};


//工厂出发
class ProcessorFactory{
public:
    virtual ~ProcessorFactory(){}
    virtual processors* create(const std::vector<std::string>& args) = 0;
};
class TrimFactory:public ProcessorFactory{
public:
    processors* create(const std::vector<std::string>& args)override {
        if(!args.empty()){
            return nullptr;
        }
        return new Trim();
    }
};
class UpperFactory : public ProcessorFactory {
public:
    processors* create(const std::vector<std::string>& args)override {
        if(!args.empty()){
            return nullptr;
        }
        return new Upper();
    }
};
class ReplaceFactory : public ProcessorFactory {
public:
    processors* create(const std::vector<std::string>& args)override {
        if (args.size() != 2){
            return nullptr;
        }
        return new Replace(args[0],args[1]);
    }
};



//注册表部分
class Register{
    public:
    Register(const Register&)=delete;
    Register&operator=(const Register&)=delete;

    static Register& instance(){
        static Register reg;
        return reg;
    }

    processors* create(const std::string& name, const std::vector<std::string>& args) {
        for (const auto& entry : registry) {
            if (entry.name == name) {
                return entry.factory->create(args);
            }
        }
        return nullptr;
    }


    private:
    struct registerentry{
        std::string name;
        ProcessorFactory* factory; 
    };
    std::vector<registerentry> registry;

    Register(){
        registry.push_back({"trim", new TrimFactory()});
        registry.push_back({"upper", new UpperFactory()});
        registry.push_back({"replace", new ReplaceFactory()});
    }
    ~Register(){ 
        for (auto& entry : registry) {
            delete entry.factory;
        }
    }
    
};

//流水线部分
struct step{
    std::string name;
    std::vector<std::string> args;
};
void split(std::string str,char c,std::vector<std::string>&tokens){
    std::string token;
    size_t begin=0,found=str.find(c);
        while(found!=std::string::npos){
            token.clear();
            tokens.push_back(str.substr(begin, found - begin));
            begin = found + 1;
            found = str.find(c, begin);
        }
        tokens.push_back(str.substr(begin)); 
}
std::vector<step> intosteps(const std::string pipeline,bool &ok){
    std::vector<step>steps;
    std::vector<std::string> tokens;
    split(pipeline,'|',tokens);

    if(tokens.empty()){
        return {};
    }
    for(const std::string& token:tokens){
        if(token.empty()){
            ok=false;
            return {};
        }
        size_t colon=token.find(':');
        if(colon==std::string::npos){
            steps.push_back({token,{}});
        }else{
            std::vector<std::string> args;
            split(token.substr(colon+1),':',args);
            steps.push_back({token.substr(0,colon),args});
        }
    }
    ok=true;
    return steps;

};

std::vector<std::string> RunTextPipeline(const std::string& pipeline, const std::vector<std::string>& lines, bool& ok) {
    Register& registry=Register::instance();
    std::vector<step>steps=intosteps(pipeline,ok);
    if(!ok){
        return {};
    }

    std::vector<processors*>processorlist;
    for(const step& step:steps){
        processors*processor=registry.create(step.name,step.args);
        if(!processor){
            cleanprocessor(processorlist);
            ok=false;
            return {};
        }
        processorlist.push_back(processor);
    }

    std::vector<std::string>result;
    for(const std::string& line:lines){
        std::string processed =line;

        for(processors* processor:processorlist){
            processed=processor->process(processed);
        }
        result.push_back(processed);
    }

    cleanprocessor(processorlist);

    ok=true;
    return  result;
}

// ==================== A0-10 Rule Engine ====================

std::vector<long long> RunRuleEngine(
    const std::vector<std::string>& rule_specs,
    const std::vector<Event>& events,
    long long& total_any,
    bool& ok
) {
    (void)rule_specs;
    (void)events;
    total_any = 0;
    ok        = false;
    return {};
}

// ==================== A0-11 Command Dispatcher====================

std::string RunCommandDispatcher(const std::string& full_stdin, bool& ok) {
    (void)full_stdin;
    ok = false;
    return "FAIL\n";
}

} // namespace rm_a0
