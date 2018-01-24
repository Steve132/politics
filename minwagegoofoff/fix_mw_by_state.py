import csv

def fixcell(c):

	c=''.join([sc for sc in c if sc in '0123456789. &-\xe2'])	
	
	splitc=None
	for psc in '-\xe2&-':
		if(psc in c):
			splitc=psc
			break

	if(splitc):
		c=str(max([float(a) for a in c.split(splitc)]))

	return c

def fixrow(p):
	return [p[0]]+[fixcell(a) for a in p[1:]]

with open('rawdata/raw_minwage_by_state.csv','rb') as f:
	with open('minwage_by_state.csv','wb') as fout:
		cw=csv.writer(fout)		
		for p in csv.reader(f):
			cw.writerow(fixrow(p))

