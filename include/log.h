#include <iostream>

class Log
{
    private:
        std::ostream& m_cout;

        bool m_print;
        bool m_quitOnMessageEnd;

    public:
        Log(std::ostream& cout = std::cout);
        Log(Log const& other);
        ~Log();

        template<class T>
        Log& operator<<(T const& val)
        {
            if(m_print) m_cout << val;
            return *this;
        }

        /**
         * @brief Ensures that a given test is true.
         * If the test is true, the message is not displayed and nothing happens.
         * If the test is false, the message is displayed and the application stops.
         *
         * example:
         * ```
         * Log::ensure(x >= 0) << "x is negative!";
         * ```
         *
         * @return a Log stream for the message.
         */
        static Log ensure(bool test);
};
