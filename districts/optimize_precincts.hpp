#ifndef OPTIMIZE_PRECINCTS_HPP
#define OPTIMIZE_PRECINCTS_HPP

#include <unordered_set>
#include <unordered_map>
#include <set>
#include <string>
#include <algorithm>

typedef size_t precinct_id_t;

typedef std::unordered_set<precinct_id_t> PrecinctSet;

class AdjacencyData
{
private:
	std::unordered_map<std::string,precinct_id_t> m_sid2uidmap;
	std::vector<std::string> m_uid2sidmap;
	std::vector<PrecinctSet> m_adjacencies;
public:
	PrecinctData(const std::set<std::string>& identifiers):
		m_adjacencies(identifiers.size()),
		m_uid2sidmap(identifiers.cbegin(),identifiers.cend())
	{
		size_t ui=0;
		for(const std::string& sid : m_uid2sidmap)
		{
			m_sid2uidmap[sid]=ui++;
		}
	}
	size_t num_precincts() const
	{
		return m_precincts.size();
	}
	size_t identifier2uid(const std::string& identifier) const
	{
		return m_sid2uidmap[identifier];
	}
	const PrecinctSet& adjacencies(const std::size_t uid) const
	{
		return m_precincts[uid];
	}
};

class DistrictingSolution
{
protected:
	std::vector<size_t> m_p2di;
	std::vector<PrecinctSet> m_districts;
public:
	static const size_t NONE;

	DistrictingSolution(size_t num_districts,size_t num_precincts):
		m_districts(num_districts),
		m_p2di(num_precincts,NONE)
	{}
	const size_t num_districts() const
	{
		return m_districts.size();
	}
	const size_t num_precincts() const
	{
		return m_p2di.size();
	}
	const PrecinctSet& operator[](const size_t did) const
	{
		return m_districts[uid];
	}

	void drop(size_t did,const precinct_id_t& pid)
	{
		size_t& p2r=m_p2di[did];
		
		if(p2r==pid)
		{
			p2r=NONE;
		}
		m_districts[did].erase(pid);
	} 
	void add(size_t did,const precinct_id_t& pid)
	{
		size_t& p2r=m_p2di[did];
		if(p2r==NONE)
		{
			p2r=pid;
		}
		else if(p2r!=pid)
		{
			drop(p2r,pid);
		}
		m_districts[did].emplace(pid);
	}
};
#endif
