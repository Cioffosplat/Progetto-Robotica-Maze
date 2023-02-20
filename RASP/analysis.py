import cv2
import numpy as np
import time
import os

sift = cv2.SIFT_create()

BASE_PATH = os.path.dirname(__file__)
MIN_MATCH_COUNT = 1

u_img = cv2.imread(BASE_PATH + '/letter/u.png', cv2.IMREAD_GRAYSCALE)
u_kp, u_des = sift.detectAndCompute(u_img, None)
s_img = cv2.imread(BASE_PATH + '/letter/s.png', cv2.IMREAD_GRAYSCALE)
s_kp, s_des = sift.detectAndCompute(s_img, None)
h_img = cv2.imread(BASE_PATH + '/letter/h.png', cv2.IMREAD_GRAYSCALE)
h_kp, h_des = sift.detectAndCompute(h_img, None)

FLANN_INDEX_KDTREE = 1
index_params = dict(algorithm=FLANN_INDEX_KDTREE, trees=5)
search_params = dict(checks=10)
flann = cv2.FlannBasedMatcher(index_params, search_params)

draw_params = dict(matchColor=(0, 255, 0),
                   singlePointColor=(255, 0, 0),
                   flags=cv2.DrawMatchesFlags_DEFAULT)


def filter_matches(matches, mask):
    good = 0
    for i, (m, n) in enumerate(matches):
        if m.distance < 0.7 * n.distance:
            mask[i] = [1, 0]
            good += 1
    return good


def read_letter(frame, debug=False):
    frame_kp, frame_des = sift.detectAndCompute(frame, None)

    try:
        u_matches = flann.knnMatch(u_des, frame_des, k=2)
        s_matches = flann.knnMatch(s_des, frame_des, k=2)
        h_matches = flann.knnMatch(h_des, frame_des, k=2)
    except cv2.error:
        return ''

    u_mask = [[0, 0] for _ in range(len(u_matches))]
    s_mask = [[0, 0] for _ in range(len(s_matches))]
    h_mask = [[0, 0] for _ in range(len(h_matches))]

    u_good = filter_matches(u_matches, u_mask)
    s_good = filter_matches(s_matches, s_mask)
    h_good = filter_matches(h_matches, h_mask)

    if debug:
        # print(f'u: {u_good}, s: {s_good}, h: {h_good}')
        draw_params.update({'matchesMask': u_mask})
        cv2.imshow('u', cv2.drawMatchesKnn(u_img, u_kp, frame, frame_kp, u_matches, None, **draw_params))
        draw_params.update({'matchesMask': s_mask})
        cv2.imshow('s', cv2.drawMatchesKnn(s_img, s_kp, frame, frame_kp, s_matches, None, **draw_params))
        draw_params.update({'matchesMask': h_mask})
        cv2.imshow('h', cv2.drawMatchesKnn(h_img, h_kp, frame, frame_kp, h_matches, None, **draw_params))

    # if h_good > 4:
    #     return 'h'
    # elif u_good > 3:
    #     return 'u'
    # elif s_good > 4:
    #     return 's'

    # magic
    if u_good > 2 and s_good > h_good:
        u_good += 2

    res = [u_good, s_good, h_good]
    max_letter = max(res)
    if max_letter > 1:
        return ('u', 's', 'h')[res.index(max_letter)]
    return ''


def read_color(frame, debug=False):
    MIN_SATURATION = 75
    MIN_VALUE = 100

    hsv = cv2.cvtColor(255 - frame, cv2.COLOR_BGR2HSV)

    buckets = [180 // 2, 240 // 2, 300 // 2]
    labels = ['r', 'y', 'g']
    delta = 30

    masks = [cv2.inRange(hsv, (b - delta, MIN_SATURATION, MIN_VALUE), (b + delta, 255, 255)) for b in buckets]
    if debug:
        cv2.imshow('hsv', cv2.cvtColor(hsv, cv2.COLOR_HSV2BGR))
        for i, m in enumerate(masks):
            cv2.imshow(str(i), cv2.copyTo(frame, m))

    count_masks = [np.count_nonzero(m) for m in masks]

    max_color = max(count_masks)
    if max_color > 5_000:
        return labels[count_masks.index(max_color)]
    return ''


def read_all(camera, debug=False):
    while not camera.frame()[0]:
        if debug:
            cv2.waitKey(1)
        else:
            time.sleep(.001)

    frames = []
    while len(frames) < MIN_MATCH_COUNT:
        if debug:
            print('shot')
        ret, frame, frame_gray = camera.frame()
        # cv2.imwrite(f'd/frame-{time.time()}-{camera.right}.png', frame)
        if ret:
            frames.append([frame, frame_gray])
        if debug:
            cv2.waitKey(1)
        else:
            time.sleep(.001)

    letters = []
    colors = []
    for frame, frame_gray in frames:
        letters.append(read_letter(frame_gray, debug))
        colors.append(read_color(frame, debug))

    max_letter = max(set(letters), key=letters.count)
    max_color = max(set(colors), key=colors.count)
    return max_letter, max_color
