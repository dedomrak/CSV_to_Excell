#include "BasicExcel.hpp"
#include "../CSVParser/csvparser.h"
using namespace YExcel;

int main(int argc, char* argv[])
{
  BasicExcel e;

  // Load a workbook with one sheet, display its contents and
  // save into another file.
   char *fileName = "input2.csv";
  FILE *fp =fopen(fileName,"r");
  if (!fp) {
      printf("Could't open file!\n");
      return 1;
  }
  int retVal = 0;
  CSVParser csv;
  printf("Parse %s  file!\n",fileName);
  retVal = csv.Parse(fp);

  std::vector<char *>parsedStrings =  csv.getValuesVector();

  // Create a new workbook with 2 worksheets and write some contents.
  e.New(1);
  e.RenameWorksheet("Sheet1", "Test1");
  BasicExcelWorksheet* sheet = e.GetWorksheet("Test1");
  BasicExcelCell* cell;
  if (sheet)
  {
      for (size_t c=0; c<=5; ++c)
      {
          cell = sheet->Cell(0,c);
          cell->Set((int)c);
      }
      if(parsedStrings.size()%5) {
          do {
              parsedStrings.push_back("added");
          }
          while(parsedStrings.size()%5);
      }
      int row = 1;
      int column =1;
      int index =0;
      for(auto it = parsedStrings.begin(); it != parsedStrings.end(); ++it) {
          char * val = *it;
          sheet->Cell(row,column+index)->SetString(val);
          index++;
          if(index==5) {
              row++;
              column = 1;
              index = 0;
          }

      }

  }

  e.SaveAs("example1.xls");

  // Load the newly created sheet and display its contents
  e.Load("example1.xls");

  size_t maxSheets = e.GetTotalWorkSheets();
  cout << "Total number of worksheets: " << e.GetTotalWorkSheets() << endl;
  for (size_t i=0; i<maxSheets; ++i)
  {
    BasicExcelWorksheet* sheet = e.GetWorksheet(i);
    if (sheet)
    {
      size_t maxRows = sheet->GetTotalRows();
      size_t maxCols = sheet->GetTotalCols();
      cout << "Dimension of " << sheet->GetAnsiSheetName() <<
         " (" << maxRows << ", " << maxCols << ")" << endl;

      if (maxRows>0)
      {
        printf(" ");
        for (size_t c=0; c<maxCols; ++c) printf("%10d", c+1);
        cout << endl;
      }

      for (size_t r=0; r<maxRows; ++r)
      {
        printf("%10d", r+1);
        for (size_t c=0; c<maxCols; ++c)
        {
          cout << setw(10) << *(sheet->Cell(r,c));
        // Another way of printing a cell content.
        }
        cout << endl;
      }
    }
    cout << endl;
  }
  return 0;
}
