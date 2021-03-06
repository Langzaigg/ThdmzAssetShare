#pragma once
#include <map>
#include <vector>
#include <memory>
#include <stdexcept>
namespace Basic{

	class CSVReader final{
    private:
        std::vector<std::vector<std::string> > m_csvCache;
        uint16_t m_x,m_y;

        //void loadFromBin(const std::shared_ptr<std::vector<uint8_t> >&);
        void loadFromText(const std::shared_ptr<std::vector<uint8_t> >&);
	public:
        void Load(const std::string& csv);
		std::string PopString() ;
        double PopDouble() ;
        int PopInt() ;
        bool LineEnd() const ;
        bool NextLine() ;
        bool IsLastLine() const ;
        void Reset() ;

		class ValueNotFound :public std::runtime_error {
			using std::runtime_error::runtime_error;
		};

		class InvalidCSV :public std::runtime_error {
			using std::runtime_error::runtime_error;
		};
	};
}

