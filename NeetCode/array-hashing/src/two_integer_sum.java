import java.util.Scanner;
import java.util.HashMap;
import java.util.Arrays;

class Solution {
    public int[] twoSum(int[] nums, int target) {
        
        HashMap<Integer, Integer> lookup = new HashMap<>();

        for (int i = 0; i < nums.length; i++) {

            int diff = target - nums[i];
            
            if (lookup.containsKey(diff)) {
                return new int[]{lookup.get(diff), i};
            }
            
            lookup.put(nums[i], i);
        }

        return new int[0];
    }
}

public class two_integer_sum {
    public static void main(String[] args) {

        Scanner sc = new Scanner(System.in);
        int size = sc.nextInt();
        int[] nums = new int[size];

        for (int i = 0; i < size; i++) {
            nums[i] = sc.nextInt();
        }

        int target = sc.nextInt();

        Solution sol = new Solution();

        System.out.println(Arrays.toString(sol.twoSum(nums, target)));

        sc.close();
    }
}