package Cycle3;
import java.util.*;
public class QuickSort {

	public static void main(String[] args) {
		Scanner sc=new Scanner(System.in);
		System.out.println("Enter the number of names:");
		int n=sc.nextInt();
		String[] names=new String[n];
		System.out.println("Enter the names:");
		for(int i=0;i<n;i++) {
			names[i]=sc.next();
		}
		QuickSort(names,0,n-1);
		System.out.println("The sorted names are:");
		for(int i=0;i<n;i++) {
			System.out.println(names[i]);
		}
	}
	public static void QuickSort(String[] names,int left,int right) {
		if(left<right) {
			int pivot=partition(names,left,right);
			QuickSort(names,left,pivot-1);
			QuickSort(names,pivot+1,right);
		}
	}
	public static int partition(String[] names,int left,int right) {
		String pivot=names[right];
		int i=left-1;
		for(int j=left;j<right;j++) {
			if(names[j].compareTo(pivot)<0) {
				i++;
				String temp=names[i];
				names[i]=names[j];
				names[j]=temp;
			}
		}
		String temp=names[i+1];
		names[i+1]=names[right];
		names[right]=temp;
		return i+1;
	}
}