# include <iostream>
# include <string>
#include <vector>
#include <cmath>
#include <math.h>
#include <algorithm>
#include <random>
#include <fstream>
#include <sstream>


const std::vector<std::string> vec_albet = {"a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t","u","v","w","x","y","z"};


template< typename T >
std::vector<T> reversed(std::vector<T> data){
    std::vector<T> to_return(data);
    std::reverse(to_return.begin(), to_return.end());
    return to_return;
} 

template< typename T>
void print(std::vector<T> data, bool reversed = false){
    if (reversed == false){
        for (T elem: data){
            std::cout<< elem;
        }   
    }else{
        std::reverse(data.begin(), data.end());
        for (T elem: data){
            std::cout<< elem ; //<< std::endl;
        }   
    }
    std::cout<< std::endl;
}

template< typename T>
int lenght(std::vector<T> data){
    return data.size();
}

template<typename T>
std::vector<T> slice(std::vector<T> data, int first_ind, int second_ind){
    if (second_ind > lenght(data)){
        std::cout<<"Second ind error";
        return data;
    }
    if (first_ind < 0){
        std::cout<<"First ind error";
    }
    std::vector<T> new_data;
    for(int ind= first_ind; ind<second_ind; ind++){
        new_data.push_back(data[ind]);
    }
    return new_data;
}

class DataGenerator{
    private:
        template< typename T >
        std::vector<T> reversed(std::vector<T> data){
            std::vector<T> to_return;
            return(data);
            std::reverse(to_return.begin(), to_return.end());
            return to_return;
        } 
        template<typename T>
        std::vector<T> slice(std::vector<T> data, int first_ind, int second_ind){
            if (second_ind > lenght(data)){
                std::cout<<"Second ind error";
                return data;
            }
            if (first_ind < 0){
                std::cout<<"First ind error";
            }
            std::vector<T> new_data;
            for(int ind= first_ind; ind<second_ind; ind++){
                new_data.push_back(data[ind]);
            }
            return new_data;
        }

        std::vector<int> itamaraca(int n, int N,int S0,int S1,int S2){
            const int X=4;
            std::vector<int> to_return;
            for (int i =0; i <n; i++){
                int p = std::abs(S2 - S1 + S1 - S0);
                int result = std::abs(N - (p * std::sqrt(X)));
                to_return.push_back(result);
                S0 = S1;
                S1 = S2;
                S2 = p;
            }
            return to_return;
        }  
        std::vector<std::vector<int>> combinations(int k, int n){
            std::vector<int> result;
            std::vector<std::vector<int>> to_return;
            result.push_back(-1);
            for(int i=1; i<= k; i++){
                result.push_back(i);
            }
            int j = 1;
            while (j!=0){
                to_return.push_back(slice(result, 1, result.size()));
                j = k;
                while(result[j] == n - k + j){
                    j -- ;
                }
                result[j] ++ ;
                for (int i = j +1; i <= k; i ++){
                    result[i] = result[i-1] +1;
                }
            }
            return to_return;
        }
        std::vector<std::vector<int>> gray_code(int n ){
            std::vector<std::vector<int>> to_return;
            std::vector<int> result;
            std::vector<int> helper;
            for (int j = 0; j <=n + 1; j++){
                result.push_back(0);
                helper.push_back(j + 1);
            }
            int i;
            while (i < n + 1){
                to_return.push_back(reversed(slice(result, 1, n + 1)));
                i = helper[0];
                result[i] = (result[i] == 0) ? 1 :0;
                helper[i-1] = helper[i];
                helper[i] = i+1;
                if (i != 1){
                    helper[0] = 1;
                }
            }
            return to_return;
        }
        std::vector<std::vector<int>> generate_some_random_digits(int n){
            std::vector<std::vector<int>> to_return; 
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> distr_hours(23, 23);
            std::uniform_int_distribution<> distr_minutes(0, 59);
            for (int i = 0; i < n; i ++){
                to_return.push_back({distr_hours(gen),
                     distr_minutes(gen)});
            }
            return to_return;
        }
        std::vector<std::string> generate_days_of_weeks(int n){
            std::vector<std::string> to_return;
            auto data = gray_code(7);
            std::cout<<"Gray size: "<<data.size()<<std::endl;
            int count=0;
            while (count <n){
                std::string result = "";
                for (int ind = 0; ind < 7; ind++){
                    if (data[count % data.size()][ind] == 1){
                        if (ind == 0){
                            result += "Mon ";
                        }else if (ind == 1)
                        {
                            result += "Tue ";
                        }else if (ind ==2){
                            result += "Wed ";
                        }else if (ind == 3){
                            result += "Thu ";
                        }else if (ind == 4){
                            result += "Fri ";
                        }else if (ind == 5){
                            result += "Sat ";
                        }else if (ind == 6){
                            result += "Sun";
                        }
                        
                    }
                }
                to_return.push_back(result);
                count ++;
            }
        return to_return;
        }
    public:
    std::string output_file_root;
    int n;
    std::vector<std::string> generate_data_to_file(int n){
        //n - count of data
        auto time_data = generate_some_random_digits(n);
        auto comb_data_alpha = combinations(2, 26);
        auto comb_data_digits = combinations(3, 10);
        auto cost_data = itamaraca(n, 10000, 490, 13, 65);
        auto day_of_week_data = generate_days_of_weeks(n);
        std::vector<std::string> result;
        for (int ind = 0; ind < n; ind ++){
            std::string to_result;
            to_result += vec_albet[comb_data_alpha[ind % comb_data_alpha.size()][0] - 1] + vec_albet[comb_data_alpha[ind % comb_data_alpha.size()][1] - 1];
            to_result += std::to_string(comb_data_digits[ind % comb_data_digits.size()][0] - 1) + std::to_string(comb_data_digits[ind % comb_data_digits.size()][1] - 1)+ std::to_string(comb_data_digits[ind % comb_data_digits.size()][2] - 1) + ",";
            to_result += std::to_string(time_data[ind][0]) + ":" + std::to_string(time_data[ind][1]) + ",";
            to_result += std::to_string(cost_data[ind]) + ",";
            to_result += day_of_week_data[ind];
            result.push_back(to_result);
        }
        return result;
    }
};

int main(){
    int n; 
    DataGenerator generator;
    std::string output_file_root;
    std::cout << "Enter number of data: "<<std::endl;
    std::cin>>n;
    std::cout<< "Enter path to output file (start from disk): "<<std::endl;
    std::cin>>output_file_root;
    auto data = generator.generate_data_to_file(n);
    std::ofstream writer(output_file_root);
    for (auto line:data){
        writer<<line + "\n";
    }
    std::cout<<"Done!!!";   
}