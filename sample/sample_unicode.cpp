#include <iostream>
#include <locale>
#include <string>
#include <simstring/simstring.h>

void retrieve(
    simstring::reader& dbr,
    const std::wstring& query,
    int measure,
    double threshold
    )
{
    // Retrieve similar strings into a string vector.
    std::vector<uint64_t> retval;
    dbr.retrieve(query, measure, threshold, std::back_inserter(retval));

    // Output the retrieved strings separated by ", ".
    for (int i = 0;i < (int)retval.size();++i) {
        std::wcout << (i != 0 ? L", " : L"") << retval[i];
    }
    std::wcout << std::endl;
}

int main(int argc, char *argv[])
{
    // Activate std::wcout.
    std::locale::global(std::locale(""));
    std::wcout.imbue(std::locale(""));

    // Open a SimString database for writing (with std::wstring).
    simstring::ngram_generator gen(3, false);
    simstring::writer_base<std::wstring> dbw(gen, "sample_unicode.db");
    dbw.insert(L"スパゲティ", 12345678901234);
    dbw.close();

    // Open the database for reading.
    simstring::reader dbr;
    dbr.open("sample_unicode.db");

    // Output similar strings from Unicode queries.
    retrieve(dbr, L"スパゲティー", simstring::cosine, 0.6);

    return 0;
}
