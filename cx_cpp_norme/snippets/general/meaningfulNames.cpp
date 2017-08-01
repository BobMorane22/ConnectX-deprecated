// Not OK: unclear, needs analysis from reader.
double mean(std::vector<double> V)
{
    double x{0.0};

    for(auto& v : V)
    {
        x += v;
    }

    return x / V.size();
}

// OK: very clear
double meanValue(std::vector<double> p_dataPoints)
{
    double sumOfAllPoints{0.0};

    for(auto& dataPoint : p_dataPoints)
    {
        sumOfAllPoints += dataPoint;
    }

    return sumOfAllPoints / p_dataPoint.size();
}
