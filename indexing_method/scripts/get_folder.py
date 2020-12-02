import sys
import math
i_value = float(sys.argv[1])
cd = float(sys.argv[2])
value = math.ceil((i_value - 675*(cd -1))/75)
print(value)