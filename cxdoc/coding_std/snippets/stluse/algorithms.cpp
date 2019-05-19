// OK: clear
double meanValue(std::vector<double> p_dataPoints)
{
	double sumOfAllPoints{0};

	for(auto& dataPoint : p_dataPoints)
	{
		sumOfAllPoints += dataPoint;
	}

	return sumOfAllPoints / p_dataPoint.size();
}

// Even better: self documenting; No loops!
double meanValue(std::vector<double> p_dataPoints)
{
	double sumOfAllPoints = std::accumulate(p_dataPoints.begin(),
											p_dataPoints.end(),
											0.0);

	return sumOfAllPoints / p_dataPoint.size();
}