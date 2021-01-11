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
  assert 1 <= subtask <= 8
  vr = VerifierReader(sys.stdin.read())

  maxN = 100000
  maxXY = 10**9
  maxC = 10**9
  maxR = 10**9

  if subtask == 3:
    maxN = 1000
    maxC = 0

  if subtask == 4:
    maxN = 1000

  if subtask == 5:
    maxXY = 1000
    maxR = maxR = 0

  if subtask == 6:
    maxR = maxC = 0

  if subtask == 7:
    maxC = 0

  N = vr.ReadInt(1, maxN)
  assert vr.ReadChar() == ' ', 'Input is not space separated.'
  points = vr.ReadIntList(4, -maxXY, maxXY)

  X, Y, R, C = [], [], [], []
  for _ in range(N):
    X.append(vr.ReadInt(-maxXY, maxXY))
    assert vr.ReadChar() == ' ', 'Input is not space separated.'
    Y.append(vr.ReadInt(-maxXY, maxXY))
    assert vr.ReadChar() == ' ', 'Input is not space separated.'
    R.append(vr.ReadInt(0, maxR))
    assert vr.ReadChar() == ' ', 'Input is not space separated.'
    C.append(vr.ReadInt(0, maxC))
    vr.ReadEndl()

  if subtask == 1:
    assert N == 5 and points == [1, 1, 4, 4] and \
           X == [2, 2, 3, 3, 4] and \
           Y == [1, 2, 2, 3, 3] and \
           R == [0, 0, 0, 0, 0] and \
           C == [0, 0, 0, 0, 0], \
           'Input does not satisfy subtask 1.'

  if subtask == 2:
    assert N == 9 and points == [0, 15, 10, 1] and \
           X == [2, 5, 8, 2, 5, 8, 2, 5, 8] and \
           Y == [4, 3, 2, 9, 8, 7, 14, 13, 12] and \
           R == [1, 1, 1, 1, 1, 1, 1, 1, 1] and \
           C == [7, 13, 9, 2, 3, 3, 13, 7, 11], \
           'Input does not satisfy subtask 2.'

  vr.ReadEof()


if __name__ == '__main__':
  sys.exit(main(sys.argv))
