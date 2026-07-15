import java.util.Scanner;
import java.util.Arrays;

class Solution 
{
    public int[] productExceptSelf(int[] nums) 
    {
        int n = nums.length;
        int[] res = new int[n];

        res[0] =  1;
        for (int i = 1; i < n; i++)
        {
            res[i] = res[i - 1] * nums[i - 1];
        }

        int postfix = 1;
        for (int i = n - 1; i >= 0; i --)
        {
            res[i] *= postfix;
            postfix *= nums[i];
        }

        return res;
    }
}

public class products_of_array_except_self 
{
    public static void main(String[] args) 
    {
        Scanner sc = new Scanner(System.in);
        int size = sc.nextInt();
        int[] nums = new int[size];

        for (int i = 0; i < size; i++) nums[i] = sc.nextInt();

        Solution sol = new Solution();

        System.out.println(Arrays.toString(sol.productExceptSelf(nums)));

        sc.close();
    }
}