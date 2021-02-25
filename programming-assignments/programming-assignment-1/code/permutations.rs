fn main() {
    permutations(vec![1, 2, 3, 4, 5, 6, 7, 8, 9, 10]);
}

fn permutations(nums: Vec<i32>) -> Vec<Vec<i32>> {
    let n = nums.len();
    if n == 1 {
        vec![nums]
    } else {
        let mut perms = vec![];
        let mut start_from_left = false;
        let sub_arr = nums[..n - 1].to_vec();
        let a = nums[n - 1];
        for perm in permutations(sub_arr) {
            perms.extend(insertions(a, perm, start_from_left));
            start_from_left = !start_from_left;
        }
        perms
    }
}

fn insertions(val: i32, list: Vec<i32>, start_from_left: bool) -> Vec<Vec<i32>> {
    let mut inserted_vecs = vec![];
    let mut range: Vec<usize> = (0..list.len() + 1).collect();
    if !start_from_left {
        range = range.into_iter().rev().collect();
    }
    for i in range {
        let mut sublist = list[0..i].to_vec();
        sublist.push(val);
        sublist.extend(list[i..].to_vec());
        inserted_vecs.push(sublist);
    }
    inserted_vecs
}
