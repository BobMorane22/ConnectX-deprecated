class Line2D
{
public:

	Line2D(Point2D p_firstVertex, Point2D p_secondVertex);
	double length() const;

private:

	Point2D m_firstVertex;
	Point2D m_secondVertex;
};