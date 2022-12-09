#include <iostream>
#include <fstream>
#include <thread>
#include <random>
#include <getopt.h>
#include <cstring>

using namespace std;
using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::duration;
using std::chrono::seconds;

random_device rd;
mt19937 gen(rd());
uniform_int_distribution<> distr1(0, 5001);
uniform_int_distribution<> distr2(500, 10001);

string filepath = "hg38.analysisSet.fa";
string output_path = ".";
string download_path = "https://hgdownload.soe.ucsc.edu/goldenPath/hg38/bigZips/analysisSet/hg38.analysisSet.fa.gz";

void handleChromosome(const int chr_len, string chr_name, char* chr, const int id) {
    cout << "Starting Chromosome " << chr_name << ", instance no " << id << endl;
    int q = distr1(gen);
    ofstream output_file;
    output_file.open(output_path + chr_name + "_" + to_string(id));
    char* chr_pos = chr;
    while(q < chr_len) {
        vector<char> doc;
        for(int j = distr2(gen)/10; j >= 0; j--) {
            int q_offset = distr2(gen);
            if(q + q_offset >= chr_len) {
                q += q_offset;
                chr_pos += q_offset;
                break;
            }
            output_file.write(chr_pos, q_offset);
            output_file << '\n';
            chr_pos += q_offset;
            q += q_offset;
        }
        output_file << '\n';
        output_file << '\n';
    }

    cout << "Finished Chromosome " << chr_name << ", instance no " << id << endl;
}

void handleOpts(int argc, char** argv) {
    int opt;
    while((opt = getopt(argc, argv, "I:O:")) != -1) {
        switch(opt) {
            case 'I':filepath = string(optarg);
            break;
            case 'O': output_path = string(optarg);
            break;
            default :;
        }
    }
}

int main(int argc, char **argv) {
    handleOpts(argc, argv);
    ifstream data_src;
    data_src.open(filepath);
    char* chr = nullptr;
    string chr_name;
    data_src >> chr_name;
    for(int i = 0; i < 24; i++) {
        auto start = high_resolution_clock::now();
        cout << "starting chromosome " << i << endl;
        vector<thread> threads;
        string len_str;
        int chr_len;
        chr_name.erase(0,1);
        for(int j = 0; j < 2; j++) {
            string temp;
            data_src >> temp;
        }
        data_src >> len_str;
        data_src.ignore(numeric_limits<streamsize>::max(), '\n');
        len_str.erase(0,3);
        chr_len = stoi(len_str);
        char* temp = (char *) realloc(chr, chr_len);
        if(!temp) {
            cerr << "cannot allocate space for chromosome " << i << " which required " << chr_len << " bytes" << endl;
            free(chr);
            return 1;
        }
        chr = temp;
        char* chr_insert_pos = chr;
        string cur_line;
        data_src >> cur_line;
        while (cur_line[0] != '>') {
            strncpy(chr_insert_pos, cur_line.c_str(), cur_line.length());
            chr_insert_pos += cur_line.length();
            data_src >> cur_line;
        }
        cout << "Assinging threads to chromosome no " << i << endl;
        for(int j = 0; j < 10; j++) {
            thread th(handleChromosome, chr_len, chr_name, chr, j);
            threads.push_back(std::move(th));
        }
        for (std::thread & th : threads) {
            if (th.joinable())
                th.join();
        }
        chr_name = cur_line;
        auto end = std::chrono::high_resolution_clock::now();
        auto exec_time = duration_cast<seconds>(end-start);
        cout << "finished chromosome no " << i << " in " << exec_time.count() << " seconds" << endl;
    }
    free(chr);
    return 0;

}











