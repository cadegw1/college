for i in bubbleSortByOriginalGrade.txt bubbleSortByAdjustedGrade.txt insertSortByOriginalGrade.txt insertSortByAdjustedGrade.txt selectSortByOriginalGrade.txt selectSortByAdjustedGrade.txt mergeSortByOriginalGrade.txt mergeSortByAdjustedGrade.txt quickSortByOriginalGrade.txt quickSortByAdjustedGrade.txt ;
do
	#echo ${i};
	python sortCheck.py ${i};
done
echo "   ";

