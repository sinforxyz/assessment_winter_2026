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

// ==================== A0-09 Text Pipeline================



class TextProcessor {
public:
    virtual ~TextProcessor() {}
    virtual std::string process(const std::string& input) = 0;
};
class ProcessorFactory {
public:
    virtual ~ProcessorFactory() {}
    virtual TextProcessor* create(const std::vector<std::string>& args) = 0;
};
class TrimProcessor : public TextProcessor {
public:
    std::string process(const std::string& input) override {
        if (input.empty()) return "";
        
        size_t start = 0;
        size_t end = input.size();
        while (start < end && std::isspace(static_cast<unsigned char>(input[start]))) {
            ++start;
        }
        while (end > start && std::isspace(static_cast<unsigned char>(input[end - 1]))) {
            --end;
        }
        
        return input.substr(start, end - start);
    }
};

class TrimFactory : public ProcessorFactory {
public:
    TextProcessor* create(const std::vector<std::string>& args) override {
        if (!args.empty()) {
            return nullptr;
        }
        return new TrimProcessor();
    }
};
class UpperProcessor : public TextProcessor {
public:
    std::string process(const std::string& input) override {
        std::string result = input;
        for (char& c : result) {
            if (c >= 'a' && c <= 'z') {
                c = c - 'a' + 'A';
            }
        }
        return result;
    }
};

class UpperFactory : public ProcessorFactory {
public:
    TextProcessor* create(const std::vector<std::string>& args) override {
        if (!args.empty()) {
            return nullptr;
        }
        return new UpperProcessor();
    }
};
class ReplaceProcessor : public TextProcessor {
    std::string from_;
    std::string to_;
    
public:
    ReplaceProcessor(const std::string& from, const std::string& to) 
        : from_(from), to_(to) {}
    
    std::string process(const std::string& input) override {
        if (from_.empty()) return input;
        
        std::string result;
        size_t start = 0;
        size_t found = input.find(from_);
        
        while (found != std::string::npos) {
            result.append(input, start, found - start);
            result.append(to_);
            start = found + from_.size();
            found = input.find(from_, start);
        }
        
        result.append(input, start, input.size() - start);
        return result;
    }
};

class ReplaceFactory : public ProcessorFactory {
public:
    TextProcessor* create(const std::vector<std::string>& args) override {
        if (args.size() != 2) {
            return nullptr;
        }
        return new ReplaceProcessor(args[0], args[1]);
    }
};
class ProcessorRegistry {
private:
    struct FactoryEntry {
        std::string name;
        ProcessorFactory* factory;
    };
    
    std::vector<FactoryEntry> registry_;
    
    ProcessorRegistry() {
        registry_.push_back({"trim", new TrimFactory()});
        registry_.push_back({"upper", new UpperFactory()});
        registry_.push_back({"replace", new ReplaceFactory()});
    }
    
    ~ProcessorRegistry() {
        for (auto& entry : registry_) {
            delete entry.factory;
        }
    }
    
public:
    ProcessorRegistry(const ProcessorRegistry&) = delete;
    ProcessorRegistry& operator=(const ProcessorRegistry&) = delete;
    
    static ProcessorRegistry& instance() {
        static ProcessorRegistry reg;
        return reg;
    }
    
    TextProcessor* create(const std::string& name, 
                          const std::vector<std::string>& args) {
        for (const auto& entry : registry_) {
            if (entry.name == name) {
                return entry.factory->create(args);
            }
        }
        return nullptr;
    }
    
    bool hasProcessor(const std::string& name) const {
        for (const auto& entry : registry_) {
            if (entry.name == name) {
                return true;
            }
        }
        return false;
    }
};

struct PipelineStep {
    std::string name;
    std::vector<std::string> args;
};

std::vector<PipelineStep> ParsePipeline(const std::string& pipeline_str, bool& ok) {
    std::vector<PipelineStep> steps;
    std::istringstream ss(pipeline_str);
    std::string token;
    
    while (std::getline(ss, token, '|')) {
        if (token.empty()) {
            ok = false;
            return {};
        }
        size_t colon_pos = token.find(':');
        PipelineStep step;
        
        if (colon_pos == std::string::npos) {
            step.name = token;
        } else {
            step.name = token.substr(0, colon_pos);
            
            std::string args_str = token.substr(colon_pos + 1);
            std::istringstream args_ss(args_str);
            std::string arg;
            
            while (std::getline(args_ss, arg, ':')) {
                step.args.push_back(arg);
            }
        }
        
        steps.push_back(step);
    }
    
    ok = true;
    return steps;
}
void CleanupProcessors(std::vector<TextProcessor*>& processors) {
    for (auto* processor : processors) {
        delete processor;
    }
    processors.clear();
}




std::vector<std::string> RunTextPipeline(const std::string& pipeline, 
                                         const std::vector<std::string>& lines, 
                                         bool& ok) {
    
    auto& registry = ProcessorRegistry::instance();
    
    bool parse_ok = false;
    auto steps = ParsePipeline(pipeline, parse_ok);
    if (!parse_ok || steps.empty()) {
        ok = false;
        return {};
    }
    
    // 创建处理器链（使用裸指针）
    std::vector<TextProcessor*> processors;
    
    for (const auto& step : steps) {
        if (!registry.hasProcessor(step.name)) {
            CleanupProcessors(processors);
            ok = false;
            return {};
        }
        
        TextProcessor* processor = registry.create(step.name, step.args);
        if (!processor) {
            CleanupProcessors(processors);
            ok = false;
            return {};
        }
        
        processors.push_back(processor);
    }
    
    // 处理每一行
    std::vector<std::string> results;
    results.reserve(lines.size());
    
    for (const auto& line : lines) {
        std::string processed = line;
        
        // 依次应用每个处理器
        for (auto* processor : processors) {
            processed = processor->process(processed);
        }
        
        results.push_back(processed);
    }
    
    // 清理处理器
    CleanupProcessors(processors);
    
    ok = true;
    return results;
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
