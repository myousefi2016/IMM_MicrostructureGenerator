#include "IterativeGrainScheduler.h"
#include "Eigen/Dense"
#include "Settings.h"

IterativeGrainScheduler::IterativeGrainScheduler(int numberOfThreads,
		int totalNumberOfGrains, int startIndex) :
	m_totalNumberOfThreads(numberOfThreads),
			m_totalNumberOfGrains(totalNumberOfGrains),
			m_startIndex(startIndex) {
	m_threadWorkVectors.resize(m_totalNumberOfThreads);
}
IterativeGrainScheduler::~IterativeGrainScheduler(){
}
void IterativeGrainScheduler::buildThreadWorkloads(vector<vector<Eigen::Vector3d>>& hulls, int n_gridpoints) {
	m_totalNumberOfGrains= Settings::NumberOfGrains;
	for (int i = 0; i < m_totalNumberOfThreads; i++) {
		m_threadWorkVectors.at(i).reserve(
				m_totalNumberOfGrains / m_totalNumberOfThreads + 1);
		for (int j = 0; j < m_totalNumberOfGrains / m_totalNumberOfThreads + 1; j++) {
			int id = j * m_totalNumberOfThreads + m_startIndex + i;
			if (id > m_totalNumberOfGrains)
				break;
			else
				m_threadWorkVectors.at(i).push_back(id);

		}
	}
}

vector<unsigned int>& IterativeGrainScheduler::getThreadWorkload(int threadID) {
return m_threadWorkVectors.at(threadID);
}
