import re
import string
import sys


class VerifierReader(object):
  def __init__(self, text):
    self.text = text
    self.position = 0

  def HasNext(self):
    return self.position < len(self.text)

  def Read(self, target):
    actual = self.text[self.position : self.position + len(target)]
    assert actual == target, "Could not read '{0}'".format(target)
    self.position += len(target)

  def ReadEndl(self):
    self.Read('\n')

  def ReadEof(self):
    assert self.position == len(self.text), 'Found junk at the end of the file'

  def ReadChar(self):
    assert self.position < len(self.text), 'Unexpected EOF'
    char = self.text[self.position]
    self.position += 1
    return char

  def ReadLine(self, valid_characters):
    old_position = self.position
    while True:
      assert self.position < len(self.text), 'Unexpected EOF'
      c = self.text[self.position]
      self.position += 1
      if c == '\n':
        break
      assert c in valid_characters
    assert self.position - old_position > 1, 'Nothing before next newline'
    return self.text[old_position:self.position - 1]

  def ReadRegex(self, target_regex):
    match = re.compile(target_regex).match(self.text, self.position)
    assert match is not None, 'Could not match /%s/' % target_regex
    self.position = match.end()
    return match.group(0)

  def ReadList(self, n, read_fn, *args):
    ls = []
    for i in range(n):
      if i > 0:
        self.Read(' ')
      ls.append(read_fn())
    self.ReadEndl()
    return ls

  def ReadInt(self, inclusive_min, inclusive_max):
    value = int(self.ReadRegex(r'0|(-?[1-9][0-9]*)'))
    assert inclusive_min <= value <= inclusive_max, (
        'Failed on %d <= %d <= %d' % (inclusive_min, value, inclusive_max))
    return value

  def ReadIntList(self, n, inclusive_min, inclusive_max):
    return self.ReadList(n, lambda: self.ReadInt(inclusive_min, inclusive_max))

  def ReadString(self, valid_characters=string.ascii_letters + string.digits,
                 inc_min_len=1, inc_max_len=10**6):
    old_position = self.position
    while True:
      assert self.position < len(self.text), 'Unexpected EOF'
      c = self.text[self.position]
      if c not in valid_characters:
        break
      self.position += 1
    st = self.text[old_position:self.position]
    assert inc_min_len <= len(st) <= inc_max_len, (
        'Invalid string length: %d' % len(st))
    return st

  def ReadStringList(self, n,
                     valid_characters=string.ascii_letters + string.digits,
                     inc_min_len=1, inc_max_len=10**6):
    return self.ReadList(
        n,
        lambda: self.ReadString(valid_characters, inc_min_len, inc_max_len))


def main(argv):
  subtask = int(argv[1])
  assert 1 <= subtask <= 9
  vr = VerifierReader(sys.stdin.read())

  maxN = 200000
  maxH = 1000000000
  maxQ = 200000

  if subtask == 4:
    maxN = 1000
    maxH = 1000
    maxQ = 1

  if subtask == 5:
    maxH = 5

  if subtask == 7:
    maxQ = 1

  if subtask == 8:
    maxN = 5000

  N = vr.ReadInt(1, maxN)
  vr.ReadEndl()

  H = vr.ReadIntList(N, 0, maxH)
  maxK = sum(H)

  if subtask == 3:
    assert all(H[0] == H[i + 1] for i in range(N-1)), 'H is not a constant sequence.'

  if subtask == 6:
    assert all(H[i] <= H[i + 1] for i in range(N-1)), 'H is not an increasing sequence.'

  Q = vr.ReadInt(1, maxQ)
  vr.ReadEndl()

  K = []
  for _ in range(Q):
    K.append(vr.ReadInt(1, maxK))
    vr.ReadEndl()

  if subtask == 1:
    assert N == 5 and Q == 6 and \
           H == [3,4,5,4,3] and \
           K == [3,6,9,12,15,18], \
           'Input does not satisfy subtask 1.'

  if subtask == 2:
    assert N == 15 and Q == 7 and \
           H == [8,4,8,2,8,4,8,1,8,4,8,2,8,4,8] and \
           K == [1,2,4,8,16,32,64], \
           'Input does not satisfy subtask 2.'

  vr.ReadEof()


if __name__ == '__main__':
  sys.exit(main(sys.argv))
