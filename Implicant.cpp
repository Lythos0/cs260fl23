#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <tuple>

class Implicant
{
public:
    Implicant(const std::string &implicant, const std::vector<int> &covered_minterms = {})
        : implicant_str(implicant), implicant(initializeImplicantTuple()),
          implicant_bin(initializeImplicantBinary()), hamming_weight(initializeHammingWeight()),
          covered_minterms(initializeCoveredMinterms(covered_minterms)), is_prime(true) {}

    // Getter methods
    std::string getImplicantStr() const { return implicant_str; }
    std::tuple<char, char, char> getImplicant() const { return implicant; }
    std::tuple<int, int, int> getImplicantBin() const { return implicant_bin; }
    int getHammingWeight() const { return hamming_weight; }
    std::vector<int> getCoveredMinterms() const { return covered_minterms; }
    bool getIsPrime() const { return is_prime; }

    std::string repr() consto
    {
        return implicant_str + '(' + std::to_string(covered_minterms[0]) + ')';
    }

    // Subscript operator
    char operator[](int index) const
    {
        if (index < 0 || index >= implicant_str.size())
        {
            throw std::out_of_range("Index out of range");
        }
        return implicant_str[index];
    }

    Implicant simplify(const Implicant &another_implicant) const
    {
        if (!isImplicant(another_implicant))
        {
            throw std::invalid_argument("Another implicant must be of Implicant class.");
        }

        std::string simplified_str;
        std::vector<int> combined_minterms;

        for (size_t i = 0; i < implicant_str.size(); ++i)
        {
            if (implicant_str[i] != another_implicant.implicant_str[i])
            {
                if (simplified_str.empty())
                {
                    simplified_str += implicant_str[i];
                }
                else
                {
                    simplified_str += "'"; // Adding the complement symbol
                }
            }
            else
            {
                simplified_str += implicant_str[i];
            }
        }

        // Combine covered minterms
        combined_minterms.reserve(covered_minterms.size() + another_implicant.covered_minterms.size());
        combined_minterms.insert(combined_minterms.end(), covered_minterms.begin(), covered_minterms.end());
        combined_minterms.insert(combined_minterms.end(),
                                 another_implicant.covered_minterms.begin(),
                                 another_implicant.covered_minterms.end());

        return Implicant(simplified_str, combined_minterms);
    }

private:
    std::string implicant_str;
    std::tuple<char, char, char> implicant;
    std::tuple<int, int, int> implicant_bin;
    int hamming_weight;
    std::vector<int> covered_minterms;
    bool is_prime;

    std::tuple<char, char, char> initializeImplicantTuple() const
    {
        return std::make_tuple(implicant_str[0], implicant_str[1], implicant_str[2]);
    }

    std::tuple<int, int, int> initializeImplicantBinary() const
    {
        return std::make_tuple((implicant_str[0] == '1' ? 1 : 0),
                               (implicant_str[1] == '1' ? 1 : 0),
                               (implicant_str[2] == '1' ? 1 : 0));
    }

    int initializeHammingWeight() const
    {
        return std::get<0>(implicant_bin) + std::get<1>(implicant_bin) + std::get<2>(implicant_bin);
    }

    std::vector<int> initializeCoveredMinterms(const std::vector<int> &custom_minterms) const
    {
        if (custom_minterms.empty())
        {
            return {std::stoi(implicant_str, nullptr, 2)};
        }
        else
        {
            return custom_minterms;
        }
    }

    bool isImplicant(const Implicant &imp) const
    {
        return implicant_str == imp.implicant_str && covered_minterms == imp.covered_minterms;
    }
};

int main()
{

    Implicant implicant1("101");
    Implicant implicant2("010", {5});

    std::cout << "Implicant 1: " << implicant1.repr() << std::endl;
    std::cout << "Implicant 2: " << implicant2.repr() << std::endl;

    // Test
    try
    {
        std::cout << "Implicant 1[0]: " << implicant1[0] << std::endl;
        std::cout << "Implicant 2[2]: " << implicant2[2] << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    // Test simplify method
    Implicant simplified = implicant1.simplify(implicant2);
    std::cout << "Simplified Implicant: " << simplified.repr() << std::endl;

    return 0;
}
