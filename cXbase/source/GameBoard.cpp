/***********************************************************************************************//**
 * @file    GameBoard.cpp
 * @author  Eric Poirier
 * @date    December 2016
 * @version 0.1
 *
 * Implementation for a GameBoard utility.
 *
 **************************************************************************************************/
#include "../publicAPI/GameBoard.h"


USING_NAMESPACE_STD
USING_NAMESPACE_CXBASE


GameBoard::GameBoard(): m_grid(NB_ROWS_MIN, vector<Disc>(NB_COLUMNS_MIN, Disc())),
                        m_nbRows{NB_ROWS_MIN}, m_nbColumns{NB_COLUMNS_MIN}

{
    int nbPositionsGameBoard{0};

    for(auto& row : m_grid)
    {
        for(auto& disc : row)
        {
            if(disc == NO_DISC)
            {
                ++nbPositionsGameBoard;
            }
        }
    }

    ASSERTION(nbPositionsGameBoard >= NB_ROWS_MIN * NB_COLUMNS_MIN);
    ASSERTION(nbPositionsGameBoard <= NB_ROWS_MAX * NB_COLUMNS_MAX);
    ASSERTION(nbPositionsGameBoard ==  m_nbRows * m_nbColumns);

    INVARIANTS();
}

GameBoard::GameBoard(int p_nbRows, int p_nbColumns): m_grid(p_nbRows, vector<Disc>(p_nbColumns, NO_DISC)),
                                                     m_nbRows{p_nbRows}, m_nbColumns{p_nbColumns}

{
    PRECONDITION(p_nbRows >= NB_ROWS_MIN);
    PRECONDITION(p_nbRows <= NB_ROWS_MAX);

    PRECONDITION(p_nbColumns >= NB_COLUMNS_MIN);
    PRECONDITION(p_nbColumns <= NB_COLUMNS_MAX);

    int nbPositionsGameBoard{0};

    for(auto& row : m_grid)
    {
        for(auto& disc : row)
        {
            if(disc == NO_DISC)
            {
                ++nbPositionsGameBoard;
            }
        }
    }

    ASSERTION(nbPositionsGameBoard >= NB_ROWS_MIN * NB_COLUMNS_MIN);
    ASSERTION(nbPositionsGameBoard <= NB_ROWS_MAX * NB_COLUMNS_MAX);
    ASSERTION(nbPositionsGameBoard ==  m_nbRows * m_nbColumns);

    INVARIANTS();
}

GameBoard::Grid GameBoard::grid() const
{
    return m_grid;
}

int GameBoard::nbColumns() const
{
    return m_nbColumns;
}

int GameBoard::nbRows() const
{
    return m_nbRows;
}

int GameBoard::nbPositions() const
{
    return m_nbColumns * m_nbRows;
}

Disc GameBoard::discAtPosition(const Position& p_case) const
{
    PRECONDITION(p_case.row() >= Row{0});
    PRECONDITION(p_case.column() >= Column{0});

    PRECONDITION(p_case.row() < Row{m_nbRows});
    PRECONDITION(p_case.column() < Column{m_nbColumns});

    return m_grid[p_case.rowValue()][p_case.columnValue()];
}

Position GameBoard::placeDisc(const Column& p_column, const Disc& p_disc)
{
    PRECONDITION(p_column >= Column{0});
    PRECONDITION(p_column < Column{m_nbColumns});

    int rowSubscript{0};

    for(auto row = m_grid.begin(); row != m_grid.end(); ++row)
    {
        if(discAtPosition(Position{Row{rowSubscript}, p_column}) == NO_DISC)
        {
            m_grid[rowSubscript][p_column.value()] = p_disc;
            break;
        }

        ++rowSubscript;
    }

    INVARIANTS();

    return Position{Row{rowSubscript}, p_column};
}

bool GameBoard::isColumnFull(const Column& p_column) const
{
    PRECONDITION(p_column >= Column{0});
    PRECONDITION(p_column < Column{NB_COLUMNS_MAX});

    bool isPlayable{false};
    int rowSubscript{m_nbRows - 1};

    for(auto row = m_grid.rbegin(); row != m_grid.rend(); ++row)
    {
        if(discAtPosition(Position{Row{rowSubscript}, p_column}) == NO_DISC)
        {
            isPlayable = true;
            break;
        }

        --rowSubscript;
    }

    return !isPlayable;
}

bool GameBoard::isWinner(const Position& p_positionLastPlacedDisc, int p_inARow) const
{
    PRECONDITION(p_positionLastPlacedDisc.row() >= Row{0});
    PRECONDITION(p_positionLastPlacedDisc.column() >= Column{0});

    PRECONDITION(p_positionLastPlacedDisc.row() < Row{m_nbRows});
    PRECONDITION(p_positionLastPlacedDisc.column() < Column{m_nbColumns});

    bool isWinner = false;

    if(checkHorizontalWinner(p_positionLastPlacedDisc, p_inARow) ||
       checkVerticalWinner(p_positionLastPlacedDisc, p_inARow) ||
       checkUpwardWinner(p_positionLastPlacedDisc, p_inARow)||
       checkDownwardWinner(p_positionLastPlacedDisc, p_inARow))
    {
        isWinner = true;
    }

    return isWinner;
}

bool GameBoard::operator==(const GameBoard &p_gameBoard) const
{
    PRECONDITION(m_nbColumns == p_gameBoard.m_nbColumns);
    PRECONDITION(m_nbRows == p_gameBoard.m_nbRows);

    bool isEqual{true};
    int rowSubscript{0};
    int columnSubscript{0};

    for(auto& row :m_grid)
    {
        for(auto& position :row)
        {
            if(position != p_gameBoard.discAtPosition(Position{Row{rowSubscript}, Column{columnSubscript}}))
            {
                isEqual = false;
                break;
            }

            ++columnSubscript;
        }

        if(isEqual)
        {
            break;
        }

        columnSubscript = 0;
        ++rowSubscript;
    }

    return isEqual;
}

bool GameBoard::operator!=(const GameBoard &p_gameBoard) const
{
    PRECONDITION(m_nbColumns == p_gameBoard.m_nbColumns);
    PRECONDITION(m_nbRows == p_gameBoard.m_nbRows);

    return !(*this == p_gameBoard);
}

BEGIN_CXBASE_NAMESPACE

ostream& operator<<(ostream& p_flux, const GameBoard& p_gameBoard)
{

    int rowSubscript{p_gameBoard.nbRows() - 1};
    int columnSubscript{0};
    GameBoard::Grid grid{p_gameBoard.grid()};

    for(auto row = grid.rbegin(); row != grid.rend(); ++row)
    {
        p_flux << rowSubscript << " ";

        if(rowSubscript < 10)
            p_flux << " ";

        p_flux << "|";

        for(auto& disc : *row)
        {
            p_flux << disc;

            if(columnSubscript >= 10)
                p_flux << " ";

            p_flux << "|";

            ++columnSubscript;
        }

        p_flux << endl;

        columnSubscript = 0;
        --rowSubscript;
    }

    p_flux << "  ";

    for(columnSubscript = 0; columnSubscript < p_gameBoard.nbColumns(); ++columnSubscript)
    {
        p_flux << "   " << columnSubscript;
    }

    p_flux << endl;

    return p_flux;
}

END_CXBASE_NAMESPACE

void GameBoard::checkInvariant() const
{
    INVARIANT(m_nbRows >= NB_ROWS_MIN);
    INVARIANT(m_nbRows < NB_ROWS_MAX + 1);

    INVARIANT(m_nbColumns >= NB_COLUMNS_MIN);
    INVARIANT(m_nbColumns < NB_COLUMNS_MAX + 1);
}

int GameBoard::leftValidationLimit(Position p_positionLastPlacedDisc, int p_inARow, GridValidationType validationType) const
{
    int lastPlayedRow{p_positionLastPlacedDisc.rowValue()};
    int lastPlayedColumn{p_positionLastPlacedDisc.columnValue()};

    int leftSubscript{lastPlayedColumn - (p_inARow - 1)};
    leftSubscript = max(leftSubscript, 0);

    if(validationType == GridValidationType::ObliqueDecreasing)
    {
        int lowerSubscript{lastPlayedRow + (p_inARow - 1)};
        lowerSubscript = min(m_nbRows - 1, lowerSubscript);

        if(lastPlayedColumn - leftSubscript > lowerSubscript - lastPlayedRow)
        {
            leftSubscript = lastPlayedColumn - (lowerSubscript - lastPlayedRow);
        }
    }
    else if(validationType == GridValidationType::ObliqueIncreasing)
    {
        int upperSubscript{lastPlayedRow - (p_inARow - 1)};
        upperSubscript = max(0, upperSubscript);

        if(lastPlayedColumn - leftSubscript > lastPlayedRow - upperSubscript)
        {
            leftSubscript = lastPlayedColumn - (lastPlayedRow - upperSubscript);
        }
    }

    return leftSubscript;
}

int GameBoard::rightValidationLimit(Position p_positionLastPlacedDisc, int p_inARow, GridValidationType validationType) const

{
    int lastPlayedRow{p_positionLastPlacedDisc.rowValue()};
    int lastPlayedColumn{p_positionLastPlacedDisc.columnValue()};

    int rightSubscript{lastPlayedColumn + (p_inARow - 1)};
    rightSubscript = min(rightSubscript, m_nbColumns - 1);

    if(validationType == GridValidationType::ObliqueDecreasing)
    {
        int upperSubscript{(lastPlayedRow) - (p_inARow - 1)};
        upperSubscript = max(0, upperSubscript);

        if(rightSubscript - lastPlayedColumn > lastPlayedRow - upperSubscript)
        {
            rightSubscript = lastPlayedColumn + (lastPlayedRow - upperSubscript);
        }
    }
    else if(validationType == GridValidationType::ObliqueIncreasing)
    {
        int lowerSubscript{lastPlayedRow + (p_inARow - 1)};
        lowerSubscript = min(m_nbRows - 1, lowerSubscript);

        if(rightSubscript - lastPlayedColumn > lowerSubscript - lastPlayedRow)
        {
            rightSubscript = lastPlayedColumn + (lowerSubscript - lastPlayedRow);
        }
    }

    return rightSubscript;
}

int GameBoard::upperValidationLimit(Position p_positionLastPlacedDisc, int p_inARow, GridValidationType validationType) const
{
    int lastPlayedRow{p_positionLastPlacedDisc.rowValue()};
    int lastPlayedColumn{p_positionLastPlacedDisc.columnValue()};

    int upperSubscript{lastPlayedRow + (p_inARow - 1)};
    upperSubscript = min(m_nbRows - 1, upperSubscript);

    if(validationType == GridValidationType::ObliqueDecreasing)
    {
        int leftSubscript{lastPlayedColumn - (p_inARow - 1)};
        leftSubscript = max(leftSubscript, 0);

        if(upperSubscript - lastPlayedRow > lastPlayedColumn - leftSubscript)
        {
            upperSubscript = lastPlayedRow + (lastPlayedColumn - leftSubscript);
        }
    }
    else if(validationType == GridValidationType::ObliqueIncreasing)
    {
        int rightSubscript{lastPlayedColumn + (p_inARow - 1)};
        rightSubscript = min(rightSubscript, m_nbColumns - 1);

        if(upperSubscript - lastPlayedRow > rightSubscript - lastPlayedColumn)
        {
            upperSubscript = lastPlayedRow + (rightSubscript - lastPlayedColumn);
        }
    }

    return upperSubscript;

}

int GameBoard::lowerValidationLimit(Position p_positionLastPlacedDisc, int p_inARow, GridValidationType validationType) const
{
    int lastPlayedRow{p_positionLastPlacedDisc.rowValue()};
    int lastPlayedColumn{p_positionLastPlacedDisc.columnValue()};

    int lowerSubscript{lastPlayedRow - (p_inARow - 1)};
    lowerSubscript = max(0, lowerSubscript);

    if(validationType == GridValidationType::ObliqueDecreasing)
    {
        int rightSubscript{lastPlayedColumn + (p_inARow - 1)};
        rightSubscript = min(rightSubscript, m_nbColumns - 1);

        if(lastPlayedRow - lowerSubscript > rightSubscript - lastPlayedColumn)
        {
            lowerSubscript = lastPlayedRow - (rightSubscript - lastPlayedColumn);
        }
    }
    else if(validationType == GridValidationType::ObliqueIncreasing)
    {
        int leftSubscript = lastPlayedColumn - (p_inARow - 1);
        leftSubscript = max(leftSubscript, 0);

        if(lastPlayedRow - lowerSubscript > lastPlayedColumn - leftSubscript)
        {
            lowerSubscript = lastPlayedRow - (lastPlayedColumn - leftSubscript);
        }
    }

    return lowerSubscript;
}

int GameBoard::nbOfValidations(int p_minValidationLimit, int p_maxValidationLimit, int p_inARow) const
{
    int nbCombinationsToCheck{abs(p_maxValidationLimit - p_minValidationLimit) + 1};
    nbCombinationsToCheck = nbCombinationsToCheck - (p_inARow - 1);

    return nbCombinationsToCheck;
}

int GameBoard::horizontalNbOfAdjacentDiscs(Position p_positionLastPlacedDisc, int p_inARow) const
{

    int leftLimit{leftValidationLimit(p_positionLastPlacedDisc, p_inARow)};
    int rightLimit{rightValidationLimit(p_positionLastPlacedDisc, p_inARow)};
    int nbValidations{nbOfValidations(leftLimit, rightLimit,p_inARow)};

    int pairIdenticalDiscs{0};
    int nbIdenticalDiscs{0};

    Row rowLastPlacedDisc{p_positionLastPlacedDisc.row()};

    for(int i = leftLimit; i < leftLimit + nbValidations; ++i)
    {
        for(int j = 0; j < p_inARow - 1; ++j)
        {
            if((discAtPosition(Position{rowLastPlacedDisc, Column{i + j}}) != NO_DISC) &&
               (discAtPosition(Position{rowLastPlacedDisc, Column{i + j}}) == discAtPosition(Position{rowLastPlacedDisc, Column{i + j + 1}})))
            {
                pairIdenticalDiscs++;
            }
        }

        if(pairIdenticalDiscs == p_inARow - 1)
        {
            nbIdenticalDiscs = pairIdenticalDiscs + 1;

            break;
        }
        else
        {
            pairIdenticalDiscs = 0;
        }
    }

    return nbIdenticalDiscs;
}

int GameBoard::verticalNbOfAdjacentDiscs(Position p_positionLastPlacedDisc, int p_inARow) const
{
    int upperLimit{upperValidationLimit(p_positionLastPlacedDisc, p_inARow)};
    int limiteBas{lowerValidationLimit(p_positionLastPlacedDisc, p_inARow)};
    int nbValidations{nbOfValidations(limiteBas, upperLimit, p_inARow)};

    int pairIdenticalDiscs{0};
    int nbIdenticalDiscs{0};

    Column columnLastPlacedDisc{p_positionLastPlacedDisc.column()};

    for(int i = limiteBas; i < limiteBas + nbValidations; ++i)
    {
        for(int j = 0; j < p_inARow - 1; ++j)
        {
            if((discAtPosition(Position{Row{i + j}, columnLastPlacedDisc}) != NO_DISC) &&
               (discAtPosition(Position{Row{i + j}, columnLastPlacedDisc}) == discAtPosition(Position{Row{i + j + 1}, columnLastPlacedDisc})))
            {
                pairIdenticalDiscs++;
            }
        }

        if(pairIdenticalDiscs == p_inARow - 1)
        {
            nbIdenticalDiscs = pairIdenticalDiscs + 1;

            break;
        }
        else
        {
            pairIdenticalDiscs = 0;
        }
    }

    return nbIdenticalDiscs;
}

int GameBoard::upwardNbOfAdjacentDiscs(Position p_positionLastPlacedDisc, int p_inARow) const
{
    int limiteBas{lowerValidationLimit(p_positionLastPlacedDisc, p_inARow, GridValidationType::ObliqueIncreasing)};
    int leftLimit{leftValidationLimit(p_positionLastPlacedDisc, p_inARow, GridValidationType::ObliqueIncreasing)};
    int rightLimit{rightValidationLimit(p_positionLastPlacedDisc, p_inARow, GridValidationType::ObliqueIncreasing)};
    int nbValidations{nbOfValidations(leftLimit, rightLimit, p_inARow)};

    int pairIdenticalDiscs{0};
    int nbIdenticalDiscs{0};
    int counter{0};

    for(int i = leftLimit; i < leftLimit + nbValidations; ++i)
    {
        int k{limiteBas + counter};

        for(int j = 0; j < p_inARow - 1; ++j)
        {
            if((discAtPosition(Position{Row{k}, Column{i + j}}) != NO_DISC) &&
               (discAtPosition(Position{Row{k}, Column{i + j}}) == discAtPosition(Position{Row{k + 1}, Column{i + j + 1}})))
            {
                pairIdenticalDiscs++;
            }

            ++k;
        }

        if(pairIdenticalDiscs == p_inARow - 1)
        {
            nbIdenticalDiscs = pairIdenticalDiscs + 1;

            break;
        }

        pairIdenticalDiscs = 0;
        ++counter;
    }

    return nbIdenticalDiscs;
}

int GameBoard::downwardNbOfAdjacentDiscs(Position p_positionLastPlacedDisc, int p_inARow) const
{

    int upperLimit{upperValidationLimit(p_positionLastPlacedDisc, p_inARow, GridValidationType::ObliqueDecreasing)};
    int leftLimit{leftValidationLimit(p_positionLastPlacedDisc, p_inARow, GridValidationType::ObliqueDecreasing)};
    int rightLimit{rightValidationLimit(p_positionLastPlacedDisc, p_inARow, GridValidationType::ObliqueDecreasing)};
    int nbValidations{nbOfValidations(leftLimit, rightLimit, p_inARow)};

    int pairIdenticalDiscs{0};
    int nbIdenticalDiscs{0};
    int counter{0};

    for(int i = leftLimit; i < leftLimit + nbValidations; ++i)
    {
        int k{upperLimit - counter};

        for(int j = 0; j < p_inARow - 1; ++j)
        {
            if((discAtPosition(Position{Row{k}, Column{i + j}}) != NO_DISC) &&
               (discAtPosition(Position{Row{k}, Column{i + j}}) == discAtPosition(Position{Row{k - 1}, Column{i + j + 1}})))
            {
                ++pairIdenticalDiscs;
            }

            --k;
        }

        if(pairIdenticalDiscs == p_inARow - 1)
        {
            nbIdenticalDiscs = pairIdenticalDiscs + 1;

            break;
        }

        pairIdenticalDiscs = 0;
        ++counter;
    }

    return nbIdenticalDiscs;
}

bool GameBoard::checkHorizontalWinner(Position p_positionLastPlacedDisc, int p_inARow) const
{
    int nbAdjacentIdenticalDiscs{horizontalNbOfAdjacentDiscs(p_positionLastPlacedDisc, p_inARow)};

    return nbAdjacentIdenticalDiscs == p_inARow;
}

bool GameBoard::checkVerticalWinner(Position p_positionLastPlacedDisc, int p_inARow) const
{
    int nbAdjacentIdenticalDiscs{verticalNbOfAdjacentDiscs(p_positionLastPlacedDisc, p_inARow)};

        return nbAdjacentIdenticalDiscs == p_inARow;
}

bool GameBoard::checkUpwardWinner(Position p_positionLastPlacedDisc, int p_inARow) const
{
    int nbAdjacentIdenticalDiscs{upwardNbOfAdjacentDiscs(p_positionLastPlacedDisc, p_inARow)};

        return nbAdjacentIdenticalDiscs == p_inARow;
}

bool GameBoard::checkDownwardWinner(Position p_positionLastPlacedDisc, int p_inARow) const
{
    int nbAdjacentIdenticalDiscs{downwardNbOfAdjacentDiscs(p_positionLastPlacedDisc, p_inARow)};

        return nbAdjacentIdenticalDiscs == p_inARow;
}
