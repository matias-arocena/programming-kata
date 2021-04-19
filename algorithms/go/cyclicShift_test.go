package algorithms

import "testing"

func Test_computeRotations(t *testing.T) {
	type args struct {
		n int
		k int
		a string
	}
	tests := []struct {
		name string
		args args
		want int
	}{
		// TODO: Add test cases.
		{
			args: args{
				n: 5,
				k: 2,
				a: "10101",
			},
			want: 9,
		},
		{
			args: args{
				n: 6,
				k: 2,
				a: "010101",
			},
			want: 3,
		},
		{
			args: args{
				n: 6,
				k: 4,
				a: "010101",
			},
			want: 7,
		},
		{
			args: args{
				n: 5,
				k: 2,
				a: "01111",
			},
			want: 6,
		},
	}
	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			if got := computeRotations(tt.args.n, tt.args.k, tt.args.a); got != tt.want {
				t.Errorf("computeRotations() = %v, want %v", got, tt.want)
			}
		})
	}
}
