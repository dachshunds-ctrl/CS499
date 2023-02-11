#include <stdexcept>
#include <string>
#include <vector>
#include <list>
#include <sstream>
#include <sqlite3.h>

namespace csv
{
    class Error : public std::runtime_error
    {

      public:
        Error(const std::string &msg):
          std::runtime_error(std::string("CSVparser : ").append(msg))
        {
        }
    };

    class Row
    {
    	public:
    	    Row(const std::vector<std::string> &header, const std::vector<std::string> &values);
    	    ~Row(void);

    	public:
            unsigned int size(void) const;

        private:
    		const std::vector<std::string> _header;
    		std::vector<std::string> _values;

        public:

            template<typename T>
            const T getValue(unsigned int pos) const
            {
                if (pos < _values.size())
                {
                    T res;
                    std::stringstream ss;
                    ss << _values[pos];
                    ss >> res;
                    return res;
                }
                throw Error("can't return this value (doesn't exist)");
            }
            const std::string operator[](unsigned int) const;
            const std::string operator[](const std::string &valueName) const;
            friend std::ostream& operator<<(std::ostream& os, const Row &row);
    };

    class Parser
    {

    public:
        Parser(sqlite3 *db, const std::string &table_name);
        ~Parser(void);

    public:
        void insertRow(const std::vector<std::string> &);
        void updateRow(const std::vector<std::string> &, int id);
        void deleteRow(int id);
        Row &getRow(unsigned int id) const;
        unsigned int rowCount(void) const;
        unsigned int columnCount(void) const;
        std::vector<std::string> getHeader(void) const;
        const std::string getHeaderElement(unsigned int pos) const;

    public:
        void commit(void) const;

    private:
        sqlite3 *_db;
        std::string _table_name;
        std::vector<std::string> _header;

        int getLastInsertRowID();

        void init();
        void queryHeader();
    };
}
